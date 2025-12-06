#include "init_sgp4.h"

#include <thread>
#include <functional>

inline bool is_leap(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}


void parse_epoch_to_year_doy(const std::string& epoch, int& year, double& day_of_year) {
    int month_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int month, day, hour, minute, second, micro;
    year   = std::stoi(epoch.substr(0,4));
    month  = std::stoi(epoch.substr(5,2));
    day    = std::stoi(epoch.substr(8,2));
    hour   = std::stoi(epoch.substr(11,2));
    minute = std::stoi(epoch.substr(14,2));
    second = std::stoi(epoch.substr(17,2));
    micro  = std::stoi(epoch.substr(20,6));

    int doy = day;
    for(int m = 1; m < month; ++m) {
        doy += month_days[m-1];
        if(m == 2 && is_leap(year)) doy += 1;
    }

    double fraction = (hour + minute/60.0 + second/3600.0 + micro/3.6e9)/24.0;
    day_of_year = doy + fraction;

}

void worker(std::vector<Entity>& in, size_t start, size_t end){
    for (size_t i = start; i < end; i++){

        std::string name = in[i].tle.OBJECT_NAME.substr(0, 4) + in[i].tle.OBJECT_NAME.substr(5, 4);
        char satName[8] = {0};
        std::strncpy(reinterpret_cast<char*>(satName), name.c_str(), sizeof(satName)-1);

        int epochYr;
        double epochDays;
        parse_epoch_to_year_doy(in[i].tle.EPOCH, epochYr, epochDays);

        long long simNumber = TleAddSatFrFieldsGP(
            in[i].tle.NORAD_CAT_ID,                    // satNum
            in[i].tle.CLASSIFICATION_TYPE[0],          // secClass
            satName,                             // satName
            epochYr,                             // epochYr
            epochDays,                           // epochDays
            in[i].tle.BSTAR,                            // bstar
            in[i].tle.EPHEMERIS_TYPE,                  // ephType
            in[i].tle.ELEMENT_SET_NO,                   // elsetNum
            in[i].tle.INCLINATION,                      // incli
            in[i].tle.RA_OF_ASC_NODE,                   // node
            in[i]. tle.ECCENTRICITY,                     // eccen
            in[i]. tle.ARG_OF_PERICENTER,                // omega
            in[i].tle.MEAN_ANOMALY,                     // mnAnomaly
            in[i].tle.MEAN_MOTION,                      // mnMotion
            in[i].tle.REV_AT_EPOCH                       // revNum
        );

        in[i].id = simNumber;

        if (simNumber > 0 && Sgp4InitSat(simNumber) != 0) {
            throw std::runtime_error("SGP4 Initialization failed for satellite: " + name);
        }
    }
}


void init_sgp4(std::vector<Entity>& source){
    size_t len = source.size();
    unsigned int threads = std::thread::hardware_concurrency();
    std::vector<std::thread> pool;

    size_t block = len / threads;

    for (unsigned int t = 0; t < threads; t++) {
        size_t start = t * block;
        size_t end   = (t == threads - 1) ? len : start + block;

        pool.emplace_back(worker, std::ref(source), start, end);
    }

    for (auto& t : pool) {
        if (t.joinable()) {
            t.join();
        }
    }
    
}
