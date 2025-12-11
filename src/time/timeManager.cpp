
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
    : propagateCallback(nullptr), renderCallback(nullptr) {
    // Initialize current time
    currentTimeDS50 = calculateCurrentTimeDS50();
    simulationTimeDS50.store(currentTimeDS50.load());
}

TimeManager::~TimeManager() {
    stop();
}
 

void TimeManager::update() {
    // Update current time
    currentTimeDS50.store(calculateCurrentTimeDS50());
    static double offset = 0.0;
    // Update simulation time based on time scale
    // sanity check, fix later
    simulationTimeDS50.store(offset + currentTimeDS50.load());
    offset++;
    // Call the registered callback if it exists
    if (propagateCallback && renderCallback) {
        propagateCallback(simulationTimeDS50.load());
        renderCallback();
    }else{
        throw std::runtime_error("No callback function registered for simulation update.");
    }
}

void TimeManager::runSimulation(std::function<void(double)> propagateFunc, std::function<void()> renderFunc) {

    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    running.store(true);
    propagateCallback = propagateFunc;
    renderCallback = renderFunc;

    simulationThread = std::thread([this]() {
        TimePoint startTime = Clock::now();
        int iterationCount = 0;

        while (running.load() && iterationCount < 4) {
            TimePoint currentTime = Clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

            if (elapsed >= simulationStep.load()) {
                this->update();
                iterationCount++;
                startTime = Clock::now(); // reset startTime for next step
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(16)); 
        }
        running.store(false);
    });
}

