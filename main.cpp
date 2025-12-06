#include "src/dataLoader/dataLoader.h"
#include "src/physics/init_sgp4.h"
#include "src/utils/loadDLLs.h"
#include <iostream>

void init_app();
void cleanup();
int main() {

    init_app();

    DataLoader::CelesTrackRequest requestparams = {"CATNR", "25544", "json", SatelliteClassification::UNKNOWN};
    DataLoader::CelesTrackDataLoader loader(requestparams);
    auto result = loader.fetch_data(); 
    init_sgp4(result);

    cleanup();
    return 0;
}

void init_app(){
    utils::LoadAstroStdDlls();
}

void cleanup(){
    TleRemoveAllSats();   
    Sgp4RemoveAllSats();
    utils::FreeAstroStdDlls();
 
}