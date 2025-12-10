


#include <iostream>

// Forward declarations of test functions
void testTleParse();
void testCelesTrackUrlBuilder();
void testSpaceTrackUrlBuilder();
void testCelesTrackFetchData();
void testCelesTrackRequestPrint();
void testSpaceTrackRequestPrint();
void testSpaceTrackFetchData();

int main() {
    std::cout << "Running DataLoader Tests..." << std::endl;
    
    testTleParse();
    testCelesTrackUrlBuilder();
    testSpaceTrackUrlBuilder();
    testCelesTrackFetchData();
    testCelesTrackRequestPrint();
    testSpaceTrackRequestPrint();
    testSpaceTrackFetchData();
    
    std::cout << "All DataLoader tests passed!" << std::endl;
    return 0;
}