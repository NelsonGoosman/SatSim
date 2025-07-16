#ifndef SPACETRACKCLIENT_H
#define SPACETRACKCLIENT_H

#include <string>
#include <vector>
#include <curl/curl.h>

class SpaceTrackClient {
public:
    SpaceTrackClient(const std::string& username, const std::string& password, const std::string& cookieFile = "cookies.txt");
    ~SpaceTrackClient();

    bool login();
    bool fetch(const std::string& url, std::string& response);

private:
    std::string username_;
    std::string password_;
    std::string cookieFile_;

    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif // SPACETRACKCLIENT_H
