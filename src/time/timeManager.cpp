
#ifdef __cplusplus
extern "C" 
{
#endif

#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TimeFuncDll.h"

#ifdef __cplusplus
}
#endif

#include "timeManager.h"

#include <chrono>
#include <ctime>

double TimeManager::calculateCurrentTimeDS50(){
    using namespace std::chrono;

    // Get current time
    auto now = system_clock::now();
    std::time_t t = system_clock::to_time_t(now);

    // Convert to UTC calendar time
    std::tm utc = *std::gmtime(&t);

    int year      = utc.tm_year + 1900;   // tm_year is years since 1900
    int month     = utc.tm_mon + 1;       // tm_mon is 0-11
    int dayOfMonth = utc.tm_mday;      
    int hour      = utc.tm_hour;
    int minute    = utc.tm_min;
    double second    = utc.tm_sec;


    return TimeComps2ToUTC(year, month, dayOfMonth, hour, minute, second);
}


TimeManager::TimeManager()
    : timeScale(1.0f), currentTimeDS50(0.0), simulationTimeDS50(0.0), callback(nullptr), simulationStep(10000) {
    // Initialize current time
    currentTimeDS50.store(calculateCurrentTimeDS50());
    simulationTimeDS50.store(currentTimeDS50.load());
}
 

void TimeManager::update() {
    // Update current time
    currentTimeDS50.store(calculateCurrentTimeDS50());

    // Update simulation time based on time scale
    simulationTimeDS50.store(simulationTimeDS50.load() + timeScale.load() * (currentTimeDS50.load() - simulationTimeDS50.load()));

    if (getRenderingStatus() == TaskStatus::IN_PROGRESS) {
        // skip propagation until rendering is complete
       return;
    } 
    // Call the registered callback if it exists
    if (callback) {
        setPropagationStatus(TaskStatus::IN_PROGRESS);
        callback(simulationTimeDS50.load());
        setPropagationStatus(TaskStatus::COMPLETED);
    }else{
        throw std::runtime_error("No callback function registered for simulation update.");
    }
}

void TimeManager::runSimulation(std::function<void(double)> func) {
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    running.store(true);
    callback = func;
    simulationThread = std::thread([this]() {
        TimePoint startTime = Clock::now();
        while (running.load()) {
            TimePoint currentTime = Clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

            if (elapsed >= simulationStep.load()) {
                this->update();
                startTime += std::chrono::milliseconds(simulationStep.load()); // Reset start time after update
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Sleep briefly to prevent busy-waiting
        }
    });
    
}