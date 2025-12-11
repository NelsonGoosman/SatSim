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
    DataLoader::CelesTrackDataLoader loader(requestparams, true, true);
    auto result = loader.fetch_data(); 

    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "Fetched " << result.size() << " satellites." <<  std::endl;
    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;

    init_sgp4(result);

    TimeManager& timeManager = TimeManager::getInstance();
    timeManager.setTimeScale(2.0f); 
    timeManager.setSimulationStep(2500);

    auto propagateCB = [&result](double time){
       batch_propagate_sgp4(result, time);
    };

    auto renderCB = [&result](){
        for (auto& sat : result) {
            // For debugging, print the position of the first satellite
            std::cout << "Satellite " << sat.name << " Position (km): "
                      << "X: " << sat.current_state[0] << ", "
                      << "Y: " << sat.current_state[1] << ", "
                      << "Z: " << sat.current_state[2] << std::endl;
            break; 
        }
    };

    timeManager.runSimulation(propagateCB, renderCB);

    while (timeManager.isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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