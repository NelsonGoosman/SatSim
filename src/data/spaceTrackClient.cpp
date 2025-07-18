#include "SpaceTrackClient.h"
#include <cstring>
#include <iostream>
#include <vector>
SpaceTrackClient::SpaceTrackClient(const std::string& username, const std::string& password, const std::string& cookieFile)
    : username_(username), password_(password), cookieFile_(cookieFile) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

SpaceTrackClient::~SpaceTrackClient() {
    curl_global_cleanup();
}

bool SpaceTrackClient::login() {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string postFields = "identity=" + username_ + "&password=" + password_;

    curl_easy_setopt(curl, CURLOPT_URL, "https://www.space-track.org/ajaxauth/login");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookieFile_.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookieFile_.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback_str); // discard response
    std::string temp;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &temp);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return (res == CURLE_OK);
}

bool SpaceTrackClient::fetch(const std::string& url, std::vector<uint8_t>& response) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    response.clear();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookieFile_.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback_vec);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return (res == CURLE_OK);
}

size_t SpaceTrackClient::writeCallback_str(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}    

size_t SpaceTrackClient::writeCallback_vec(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::vector<uint8_t>* vec = static_cast<std::vector<uint8_t>*>(userp);

    const uint8_t* data = static_cast<const uint8_t*>(contents);
    vec->insert(vec->end(), data, data + totalSize);

    return totalSize;
}    