#include "simTime.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TimeFuncDll.h"
#include <chrono>
#include <ctime>

double getCurrentTimeDS50(){
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
    