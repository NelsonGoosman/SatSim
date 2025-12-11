#pragma once
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>

/*
TimeManager is a singleton class that manages simulation time and real-world time. It provides methods to get the current time in DS50 format,
update simulation time based on a time.

Timemanager waits for the simulation step to elapse (ie, every 10 seconds) of real world time, then calls the registered callback function to update the simulation state.
This callback is intended to propagate a list of satellites forward in time using SGP4 propagation, to the given simulation time. Once this is done,
a boolean flag in the main application can be set to indicate new data is available for rendering, which can then be drawn in the main render loop.
*/
enum class TaskStatus {
    IN_PROGRESS,
    COMPLETED
};

class TimeManager {
    private:
        TimeManager();
        ~TimeManager();
        TimeManager(const TimeManager&) = delete;
        TimeManager& operator=(const TimeManager&) = delete;

        /**
         * @brief Get the current time in DS50 format (days since 1950)
         * @return double Current time in DS50 format
         */
        double calculateCurrentTimeDS50();

        /**
        * @brief Run one iteration of the simulation
        */
        void update();
        std::atomic<float> timeScale{1.0f};
        std::atomic<double> currentTimeDS50{0.0};
        std::atomic<double> simulationTimeDS50{0.0};
        std::atomic<long long> simulationStep{10000}; // in milliseconds
        std::thread simulationThread;
        
        std::function<void(double)> propagateCallback;
        std::function<void()> renderCallback;
        std::atomic<bool> running{false};
        
    public:
        static TimeManager& getInstance() {
            static TimeManager instance;
            return instance;
        }

        /**
         * @brief Update the time scale varible for the simulation
         */
        void setTimeScale(float newScale) {
            timeScale.store(newScale);
        }

        /**
         * @brief Get the current simulation time in DS50 format
         */
        double getSimulationTimeDS50() {
            return simulationTimeDS50.load();
        }

        /**
         * @brief Get the last updated real-world time in DS50 format
         */
        double getCurrentTimeDS50() {
            return currentTimeDS50.load();
        }

        /**
         * @brief Update the simulation time based on the time scale and real-world time
         */
        void resetSimulationTime() {
            simulationTimeDS50.store(currentTimeDS50.load());
        }

        /** 
         * @brief Register a callback function to be called on time updates, and begin simulation loop
         */
        void runSimulation(std::function<void(double)> propagateFunc, std::function<void()> renderFunc);


        // Stop the simulation loop, do nothing for now
        void stop() {
            if (simulationThread.joinable()) {
                simulationThread.join();
            }
            running.store(false);
        }


        bool isRunning() {
            return running.load();
        }   

        void setSimulationStep(int milliseconds) {
            simulationStep.store(milliseconds);
        }
        
};

