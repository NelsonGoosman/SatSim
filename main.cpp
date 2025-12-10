#include "src/dataLoader/dataLoader.h"
#include "src/physics/init_sgp4.h"
#include "src/utils/loadDLLs.h"
#include "src/time/timeManager.h"
#include <iostream>
#include "src/physics/propagate.h"

void init_app();
void cleanup();
int main() {

    init_app();

    DataLoader::CelesTrackRequest requestparams = {"CATNR", "25544", "json", SatelliteClassification::UNKNOWN};
    DataLoader::CelesTrackDataLoader loader(requestparams);
    auto result = loader.fetch_data(); 
    init_sgp4(result);

    TimeManager& timeManager = TimeManager::getInstance();
    auto cb = [&result](double time){
       batch_propagate_sgp4(result, time);
    };
    timeManager.runSimulation(cb);

    while (timeManager.isRunning()) {
        if (timeManager.getPropagationStatus() == TaskStatus::COMPLETED) {
            timeManager.setRenderingStatus(TaskStatus::IN_PROGRESS);
            std::cout << "Doing Stuff" << std::endl;
            timeManager.setRenderingStatus(TaskStatus::COMPLETED);
        }
    }

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