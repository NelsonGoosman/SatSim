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

    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "Fetched " << result.size() << " satellites." <<  std::endl;
    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;

    init_sgp4(result);

    TimeManager& timeManager = TimeManager::getInstance();
    auto cb = [&result](double time){
       batch_propagate_sgp4(result, time);
    };
    timeManager.runSimulation(cb);

    int count = 0;
    int loopLimit = 6;
    while (timeManager.isRunning()) {
        if (timeManager.getPropagationStatus() == TaskStatus::COMPLETED) {
            timeManager.setRenderingStatus(TaskStatus::IN_PROGRESS);
            std::cout << "***********************************************************" << std::endl;
            std::cout << "Simulation Time DS50: " << timeManager.getSimulationTimeDS50() << std::endl;
            std::cout << "Current Time DS50: " << timeManager.getCurrentTimeDS50() << std::endl;
            std::cout << "Satelite Location: X: " << result[0].current_state.x 
                      << " Y: " << result[0].current_state.y 
                      << " Z: " << result[0].current_state.z << std::endl;
            std::cout << "***********************************************************" << std::endl; 
            timeManager.setRenderingStatus(TaskStatus::COMPLETED);
        }
        count++;
        if (count >= loopLimit) {
            timeManager.stop();
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