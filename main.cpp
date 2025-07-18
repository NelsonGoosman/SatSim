#include "src/data/spaceTrackClient.h"
#include <iostream>
#include <memory>

int main() {
    SpaceTrackClient client("nelsongoosman@gmail.com", "!NjpZGV3S23hjqa");

    if (!client.login()) {
        std::cerr << "Login failed\n";
        return 1;
    }

    std::vector<uint8_t> response;
     // Example URL to fetch TLE data
     // Adjust the URL as needed for your specific query
     // This URL is just an example and may not work as-is
    const std::string url = "https://www.space-track.org/basicspacedata/query/class/gp/EPOCH/%3Enow-30/MEAN_MOTION/%3E11.25/ECCENTRICITY/%3C0.25/OBJECT_TYPE/payload/orderby/NORAD_CAT_ID,EPOCH/format/3le";
    if (client.fetch(url, response)) {
        std::cout << "Fetched Data\n";
    } else {
        std::cerr << "Fetch failed\n";
    }    

    return 0;
}
