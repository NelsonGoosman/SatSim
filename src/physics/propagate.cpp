#include "propagate.h"
#include <thread>

#ifdef __cplusplus
extern "C" 
{
#endif

#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/Sgp4PropDll.h"

#ifdef __cplusplus
}
#endif

void batch_propagate_sgp4(std::vector<Entity>& sats, double ds50){

    size_t len = sats.size();
    unsigned int threads = std::thread::hardware_concurrency();
    std::vector<std::thread> pool;

    size_t block = len / threads;

    for (unsigned int t = 0; t < threads; t++) {
        size_t start = t * block;
        size_t end   = (t == threads - 1) ? len : start + block;

        pool.emplace_back(worker_propagate_sgp4, std::ref(sats), start, end, ds50);
    }

    for (auto& t : pool) {
        if (t.joinable()) {
            t.join();
        }
    }
}


void worker_propagate_sgp4(std::vector<Entity>& sats, size_t start, size_t end, double ds50UTC){
    for (size_t i = start; i < end; i++){
        double pos[3];
        Sgp4PropDs50UtcPos(sats[i].id, ds50UTC, pos);
        sats[i].current_state = {pos[0], pos[1], pos[2]};
    }
}