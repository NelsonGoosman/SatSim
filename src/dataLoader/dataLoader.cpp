#include "dataLoader.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "rapidjson/document.h"
#include "tle.h"

namespace DataLoader{

/*
#####################################################

ABSTRACT DATA LOADER DEFINITIONS

#####################################################
*/

bool AbstractDataLoader::curl_init = false;

AbstractDataLoader::AbstractDataLoader() {
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

        tle.MEAN_MOTION         = obj["MEAN_MOTION"].GetDouble();
        tle.ECCENTRICITY        = obj["ECCENTRICITY"].GetDouble();
        tle.INCLINATION         = obj["INCLINATION"].GetDouble();
        tle.RA_OF_ASC_NODE      = obj["RA_OF_ASC_NODE"].GetDouble();
        tle.ARG_OF_PERICENTER   = obj["ARG_OF_PERICENTER"].GetDouble();
        tle.MEAN_ANOMALY        = obj["MEAN_ANOMALY"].GetDouble();

        tle.EPHEMERIS_TYPE      = obj["EPHEMERIS_TYPE"].GetInt();
        tle.CLASSIFICATION_TYPE = obj["CLASSIFICATION_TYPE"].GetString();
        tle.NORAD_CAT_ID        = obj["NORAD_CAT_ID"].GetInt();
        tle.ELEMENT_SET_NO      = obj["ELEMENT_SET_NO"].GetInt();
        tle.REV_AT_EPOCH        = obj["REV_AT_EPOCH"].GetInt();

        tle.BSTAR               = obj["BSTAR"].GetDouble();
        tle.MEAN_MOTION_DOT     = obj["MEAN_MOTION_DOT"].GetDouble();
        tle.MEAN_MOTION_DDOT    = obj["MEAN_MOTION_DDOT"].GetDouble();

       
        e.tle = tle;
        e.name = tle.OBJECT_NAME;
        e.classification = this->get_class();
        result.push_back(e);
    }
    return result;
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
    std::string response = http_get(request_url);
    return tle_parse(response);
}


/*
#####################################################

SPACE TRACK DATA LOADER DEFINITIONS

#####################################################
*/

void SpaceTrackDataLoader::login(){
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
    std::string response = http_get(request_url);
    return tle_parse(response);
}


} /* !DataLoader */