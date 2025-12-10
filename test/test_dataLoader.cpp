#include "../src/dataLoader/dataLoader.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// Helper class to access protected members of AbstractDataLoader for testing
class TestDataLoader : public DataLoader::AbstractDataLoader {
public:
    using DataLoader::AbstractDataLoader::tle_parse;
    
    // Implement pure virtual methods with stubs
    std::vector<Entity> fetch_data() override { return {}; }
    std::string http_get(const std::string& url) override { return ""; }
    std::string url_builder() override { return ""; }
    const SatelliteClassification get_class() override { return SatelliteClassification::UNKNOWN; }
};

// Helper class to access protected members of CelesTrackDataLoader
class TestCelesTrackDataLoader : public DataLoader::CelesTrackDataLoader {
public:
    TestCelesTrackDataLoader(DataLoader::CelesTrackRequest& params) : DataLoader::CelesTrackDataLoader(params) {}
    using DataLoader::CelesTrackDataLoader::url_builder;
};

// Helper class to access protected members of SpaceTrackDataLoader
class TestSpaceTrackDataLoader : public DataLoader::SpaceTrackDataLoader {
public:
    TestSpaceTrackDataLoader(DataLoader::SpaceTrackRequest& params) : DataLoader::SpaceTrackDataLoader(params) {}
    using DataLoader::SpaceTrackDataLoader::url_builder;
};

void testTleParse() {
    std::cout << "Testing tle_parse..." << std::endl;
    TestDataLoader loader;
    
    // Sample JSON response from CelesTrak (simplified)
    std::string json_data = "[{\"OBJECT_NAME\": \"ISS (ZARYA)\", \"OBJECT_ID\": \"1998-067A\", \"EPOCH\": \"2023-10-26T12:00:00.000000\", \"MEAN_MOTION\": 15.5, \"ECCENTRICITY\": 0.0001, \"INCLINATION\": 51.64, \"RA_OF_ASC_NODE\": 100.0, \"ARG_OF_PERICENTER\": 50.0, \"MEAN_ANOMALY\": 20.0, \"EPHEMERIS_TYPE\": 0, \"CLASSIFICATION_TYPE\": \"U\", \"NORAD_CAT_ID\": 25544, \"ELEMENT_SET_NO\": 999, \"REV_AT_EPOCH\": 10000, \"BSTAR\": 0.00001, \"MEAN_MOTION_DOT\": 0.00002, \"MEAN_MOTION_DDOT\": 0.0}]";

    std::vector<Entity> entities = loader.tle_parse(json_data);

    assert(entities.size() == 1);
    assert(entities[0].name == "ISS (ZARYA)");
    assert(entities[0].tle.NORAD_CAT_ID == 25544);
    assert(entities[0].tle.MEAN_MOTION == 15.5);
    
    std::cout << "tle_parse passed." << std::endl;
}

void testCelesTrackUrlBuilder() {
    std::cout << "Testing CelesTrackDataLoader url_builder..." << std::endl;
    DataLoader::CelesTrackRequest requestparams = {"CATNR", "25544", "json", SatelliteClassification::UNKNOWN};
    TestCelesTrackDataLoader loader(requestparams);
    
    std::string url = loader.url_builder();
    std::string expected_url = "https://celestrak.org/NORAD/elements/gp.php?CATNR=25544&FORMAT=json";
    
    assert(url == expected_url);
    std::cout << "CelesTrackDataLoader url_builder passed." << std::endl;
}

void testSpaceTrackUrlBuilder() {
    std::cout << "Testing SpaceTrackDataLoader url_builder..." << std::endl;
    DataLoader::SpaceTrackRequest requestparams;
    requestparams.request_controller = "basicspacedata";
    requestparams.request_class = "tle_latest";
    requestparams.format = "json";
    
    TestSpaceTrackDataLoader loader(requestparams);
    
    std::string url = loader.url_builder();
    std::string expected_url = "https://www.space-track.org/basicspacedata/query/class/tle_latest/EPOCH/>now-30/MEAN_MOTION/>11.25/format/json";
    
    assert(url == expected_url);
    std::cout << "SpaceTrackDataLoader url_builder passed." << std::endl;
}

void testCelesTrackFetchData() {
    std::cout << "Testing CelesTrackDataLoader fetch_data (Network Request)..." << std::endl;
    DataLoader::CelesTrackRequest requestparams = {"CATNR", "25544", "json", SatelliteClassification::UNKNOWN};
    DataLoader::CelesTrackDataLoader loader(requestparams);
    
    try {
        auto result = loader.fetch_data();
        if (!result.empty()) {
            assert(result[0].name == "ISS (ZARYA)");
        } else {
            std::cout << "Warning: No data fetched (network issue or empty response)." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception during fetch_data: " << e.what() << std::endl;
    }
    std::cout << "CelesTrackDataLoader fetch_data test completed." << std::endl;
}

void testCelesTrackRequestPrint(){
    std::cout << "Testing CelesTrackRequestPrint..." << std::endl;
    DataLoader::CelesTrackRequest requestparams = {"CATNR", "25544", "json", SatelliteClassification::UNKNOWN};
    DataLoader::CelesTrackDataLoader loader(requestparams);
    try {
        auto result = loader.fetch_data(); 
        assert (!result.empty());
        assert (result[0].name == "ISS (ZARYA)");
    } catch (const std::exception& e) {
        std::cout << "Skipping testCelesTrackRequestPrint due to network/error: " << e.what() << std::endl;
    }
    std::cout << "CelesTrackRequestPrint passed." << std::endl;
}

void testSpaceTrackRequestPrint() {
    std::cout << "Testing SpaceTrackRequestPrint..." << std::endl;
    DataLoader::SpaceTrackRequest requestparams;
    requestparams.username = "test_user";
    requestparams.password = "test_password";
    requestparams.request_controller = "basicspacedata";
    requestparams.request_class = "tle_latest";
    requestparams.format = "json";
    requestparams._class = SatelliteClassification::UNKNOWN;
    
    // Just calling print to ensure it runs without error
    requestparams.print();
    
    std::cout << "SpaceTrackRequestPrint passed." << std::endl;
}

void testSpaceTrackFetchData() {
    std::cout << "Testing SpaceTrackDataLoader fetch_data (Network Request)..." << std::endl;
    DataLoader::SpaceTrackRequest requestparams;
    requestparams.username = "dummy_user";
    requestparams.password = "dummy_pass";
    requestparams.request_controller = "basicspacedata";
    requestparams.request_class = "tle_latest";
    requestparams.format = "json";
    
    DataLoader::SpaceTrackDataLoader loader(requestparams);
    
    try {
        auto result = loader.fetch_data();
        if (!result.empty()) {
             std::cout << "Success: Data fetched." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Expected exception during fetch_data (due to dummy credentials): " << e.what() << std::endl;
    }
    std::cout << "SpaceTrackDataLoader fetch_data test completed." << std::endl;
}