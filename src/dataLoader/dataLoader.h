/*
dataLoader.h
Contains an abstract base class declaration as well as celestrack and space track
data loader classes using libcurl
*/
#pragma once
#include <vector>
#include <string>
#include <curl/curl.h>
#include <iostream>
#include "entity.h"

namespace DataLoader{


struct CelesTrackRequest{
    /*
    format:  https://celestrak.org/NORAD/elements/gp.php?{QUERY}=VALUE[&FORMAT=VALUE]
    example: https://celestrak.org/NORAD/elements/gp.php?CATNR=25544&FORMAT=TLE
    https://celestrak.org/NORAD/elements/gp.php?CATNR=25544&FORMAT=json
    */
    std::string query;
    std::string query_value;
    std::string format;
    SatelliteClassification _class;

    void print() const {
        std::cout << "Query: " << query << std::endl;
        std::cout << "Query Value: " << query_value << std::endl;
        std::cout << "Format: " << format << std::endl;
        std::cout << "Class: " << static_cast<int>(_class) << std::endl;
    }
};

struct SpaceTrackRequest{
    /*
    Login Info
    */
    std::string username;
    std::string password;
    std::string cookieFile = "cookies.txt";
    /*
    Request Info
    */
    std::string request_controller;
    std::string request_class;
    std::string format;
    SatelliteClassification _class;

    void print() const {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Password: " << password << std::endl;
        std::cout << "Cookie File: " << cookieFile << std::endl;
        std::cout << "Request Controller: " << request_controller << std::endl;
        std::cout << "Request Class: " << request_class << std::endl;
        std::cout << "Format: " << format << std::endl;
        std::cout << "Class: " << static_cast<int>(_class) << std::endl;
    }
};

class AbstractDataLoader {
public:
    virtual ~AbstractDataLoader();
    virtual std::vector<Entity> fetch_data() = 0; 
    
protected:
    AbstractDataLoader();
    virtual std::string http_get(const std::string& url) = 0;
    virtual std::string url_builder() = 0;
    virtual const SatelliteClassification get_class() = 0;
    std::vector<Entity> tle_parse(const std::string& request_data);
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);

    CURL* curl; 


private:
    static bool curl_init;

};

/*
Celes Track Data Loader Implimnetation
*/
class CelesTrackDataLoader : public AbstractDataLoader {
public:
    /**
     * @brief Constructor
     * @param _params The paramaters required for building up the url, specifying what data to retrieve
     */
    CelesTrackDataLoader(CelesTrackRequest& _params) : params(_params) {}
    /**
     * @brief Fetches the CelesTrack data specified by the _params paramater in the constructor
     * @returns A vector of entity structs representing a satelite
     */
    std::vector<Entity> fetch_data() override;
protected:
    /**
     * @brief Makes a libcurl request to a given celeste track url
     * @param url The url to make a request to
     * @returns Plaintext of the response from celestetrack
     */
    std::string http_get(const std::string& url) override;
    /**
     * @brief builds a url based on the params given by the user in the constructor
     * @returns Correct URL to send to the celestrack server
     */
    std::string url_builder() override;
    const SatelliteClassification get_class() override {return params._class; }
private:
    CelesTrackRequest params;
};

/*
Space Track Data Loader Implementation
*/
class SpaceTrackDataLoader : public AbstractDataLoader {

public:
    /**
     * @brief Constructor
     * @param _params The paramaters required for building up the url, specifying what data to retrieve
     */
    SpaceTrackDataLoader(SpaceTrackRequest& _params) : params(_params) {}
     /**
     * @brief Fetches the SpaceTrack data specified by the _params paramater in the constructor
     * @returns A vector of entity structs representing a satelite
     */
    std::vector<Entity> fetch_data() override;

protected:
    /**
     * @brief Makes a libcurl request to a given space track url
     * @param url The url to make a request to
     * @returns Plaintext of the response from spacetrack
     */
    std::string http_get(const std::string& url) override;
    /**
     * @brief builds a url based on the params given by the user in the constructor
     * @returns Correct URL to send to the celestrack server
     */
    std::string url_builder() override;
    const SatelliteClassification get_class() override {return params._class; }


private:
    /**
     * @brief sends an authentication request to space track so data can be recieved
     */
    void login();
    SpaceTrackRequest params;
};



} /* ! Dataloader */
