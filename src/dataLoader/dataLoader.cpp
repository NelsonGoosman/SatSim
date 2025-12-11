#include "dataLoader.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <optional>
#include <functional>
#include <filesystem>
#include "rapidjson/document.h"
#include "tle.h"

namespace DataLoader{

/*
#####################################################

ABSTRACT DATA LOADER DEFINITIONS

#####################################################
*/

bool AbstractDataLoader::curl_init = false;


/*
cache_request: if true, will write the contents of the request to a local file
use_cached: if true, will use a local file if it exists instead of making the request

This is because both celestrak and spacetrack have rate limits on how often you can make requests
*/
AbstractDataLoader::AbstractDataLoader(bool cache_request, bool use_cached) : cache_request_enabled(cache_request), use_cached_enabled(use_cached) {
    if (!curl_init) {
        CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
        if (res != CURLE_OK) {
            throw std::runtime_error("curl_global_init() failed");
        }
        curl_init = true;
    }

    curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("curl_easy_init() failed");
    }
}

AbstractDataLoader::~AbstractDataLoader() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

size_t AbstractDataLoader::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t newLen = size * nmemb;
    std::string* out = static_cast<std::string*>(userp);
    out->append(static_cast<char*>(contents), newLen);
    return newLen;
}

std::vector<Entity> AbstractDataLoader::tle_parse(const std::string& request_data){

    auto get_double = [](const rapidjson::Value& val) -> double {
        if (val.IsString()) {
            return std::stod(val.GetString());
        } else if (val.IsNumber()) {
            return val.GetDouble();
        }
        return 0.0;
    };

    auto get_int = [](const rapidjson::Value& val) -> int {
        if (val.IsString()) {
            return std::stoi(val.GetString());
        } else if (val.IsNumber()) {
            return val.GetInt();
        }
        return 0;
    };

    rapidjson::Document doc;
    doc.Parse(request_data.c_str());

    if (doc.HasParseError()) {
        throw std::runtime_error("Parse error in tle_parse");
    }

    std::vector<Entity> result;
    // Loop over each object
    for (auto& obj : doc.GetArray()) {
        TleData tle;
        Entity e;      

        tle.OBJECT_NAME         = obj["OBJECT_NAME"].GetString();
        tle.OBJECT_ID           = obj["OBJECT_ID"].GetString();
        tle.EPOCH               = obj["EPOCH"].GetString();

        tle.MEAN_MOTION         = get_double(obj["MEAN_MOTION"]);
        tle.ECCENTRICITY        = get_double(obj["ECCENTRICITY"]);
        tle.INCLINATION         = get_double(obj["INCLINATION"]);
        tle.RA_OF_ASC_NODE      = get_double(obj["RA_OF_ASC_NODE"]);
        tle.ARG_OF_PERICENTER   = get_double(obj["ARG_OF_PERICENTER"]);
        tle.MEAN_ANOMALY        = get_double(obj["MEAN_ANOMALY"]);

        tle.EPHEMERIS_TYPE      = get_int(obj["EPHEMERIS_TYPE"]);
        tle.CLASSIFICATION_TYPE = obj["CLASSIFICATION_TYPE"].GetString();
        tle.NORAD_CAT_ID        = get_int(obj["NORAD_CAT_ID"]);
        tle.ELEMENT_SET_NO      = get_int(obj["ELEMENT_SET_NO"]);
        tle.REV_AT_EPOCH        = get_int(obj["REV_AT_EPOCH"]);

        tle.BSTAR               = get_double(obj["BSTAR"]);
        tle.MEAN_MOTION_DOT     = get_double(obj["MEAN_MOTION_DOT"]);
        tle.MEAN_MOTION_DDOT    = get_double(obj["MEAN_MOTION_DDOT"]);

       
        e.tle = tle;
        e.name = tle.OBJECT_NAME;
        e.classification = this->get_class();
        result.push_back(e);
    }
    return result;
}

std::string AbstractDataLoader::hash_url(const std::string& input){
    std::hash<std::string> hasher;
    size_t h = hasher(input);
    return std::to_string(h);   
}

void AbstractDataLoader::cache_request(const std::string& url, const std::string& data) {
    std::string filename = "cached_requests/cache_" + hash_url(url) + ".txt";
    std::ofstream file(filename);
    if (file.is_open()) { // will overwrite existing file
        file << url << "\n";
        file << data;
        file.close();
    } else {
        throw std::runtime_error("Failed to open cache file for writing: " + filename);
    }
}

std::optional<std::string> AbstractDataLoader::use_cached_request(const std::string& url) {
    std::string dir = "cached_requests";
    std::string target_hash = hash_url(url);
    std::string prefix = "cache_" + target_hash + ".txt";

    // Iterate through all files in the cached_requests directory
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename == prefix) {
                std::ifstream file(entry.path());
                if (file.is_open()) {
                    std::string line;
                    // Skip the first line (the URL)
                    std::getline(file, line);
                    std::ostringstream oss;
                    while (std::getline(file, line)) {
                        oss << line << "\n";
                    }
                    std::string content = oss.str();
                    // Remove trailing newline if present
                    if (!content.empty() && content.back() == '\n') {
                        content.pop_back();
                    }
                    return content;
                }
            }
        }
    }
    return std::nullopt;
}

/*
#####################################################

CELES TRACK DATA LOADER DEFINITIONS

#####################################################
*/

std::string CelesTrackDataLoader::url_builder(){
   std::ostringstream oss;
   oss << "https://celestrak.org/NORAD/elements/gp.php?" 
    << this->params.query 
    << "=" 
    << this->params.query_value 
    << "&FORMAT=" 
    << this->params.format;
   std::string url = oss.str();
   return url;
}


std::string CelesTrackDataLoader::http_get(const std::string& url){
    std::string response;
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &AbstractDataLoader::writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error(
            std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
    }

    return response;
}

std::vector<Entity> CelesTrackDataLoader::fetch_data(){
    std::string request_url = url_builder();

    if (use_cached_enabled) {
        auto cached_response = use_cached_request(request_url);
        if (cached_response.has_value()) { // if found in cache, parse it otherwise make request
            return tle_parse(cached_response.value());
        }
    }

    std::string response = http_get(request_url);
    if (cache_request_enabled) {
        cache_request(request_url, response);
    }

    return tle_parse(response);
    
}


/*
#####################################################

SPACE TRACK DATA LOADER DEFINITIONS

#####################################################
*/

void SpaceTrackDataLoader::login(){
    std::ifstream ifile(this->params.cookieFile);
    if (!ifile) {
        std::ofstream file(this->params.cookieFile);
        file.close();
    }
    // TODO: switch to in memory cookies 
    std::string postFields = "identity=" + this->params.username + "&password=" + this->params.password;
    std::string response;
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/ajaxauth/login");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, this->params.cookieFile.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, this->params.cookieFile.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &AbstractDataLoader::writeCallback); // discard response
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error(
            std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
    }
}

std::string SpaceTrackDataLoader::http_get(const std::string& url){
    std::string response;
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, this->params.cookieFile.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &AbstractDataLoader::writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error(
            std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
    }
    return response;
}


std::string SpaceTrackDataLoader::url_builder() {
    /*
    example: https://www.space-track.org/basicspacedata/query/class/gp/favorites/Amateur/EPOCH/>now-30/format/json
    */
    std::ostringstream oss;
    oss << "https://www.space-track.org/"
        << this->params.request_controller  
        << "/query/class/"
        << this->params.request_class 
        <<"/EPOCH/>now-30/MEAN_MOTION/>11.25/format/"
        << this->params.format; //format
    std::string url = oss.str();
    return url;
}


std::vector<Entity> SpaceTrackDataLoader::fetch_data(){
    login();
    std::string request_url = url_builder();
    std::string dummy = "https://www.space-track.org/basicspacedata/query/class/gp/orderby/TLE_LINE1%20asc/limit/10/emptyresult/show";
    request_url = dummy;
    std::cout << "Sanity Reminder: Using dummy url in space track fetch_data(), remember to fix later" << std::endl;

    if (use_cached_enabled) {
        auto cached_response = use_cached_request(request_url);
        if (cached_response.has_value()) { // if found in cache, parse it otherwise make request
            return tle_parse(cached_response.value());
        }
    }

    std::string response = http_get(request_url);
    if (cache_request_enabled) {
        cache_request(request_url, response);
    }

    return tle_parse(response);

}


} /* !DataLoader */