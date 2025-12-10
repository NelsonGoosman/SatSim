#pragma once
#include <functional>
#include <thread>
#include <atomic>
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
        TimeManager(const TimeManager&) = delete;
        TimeManager& operator=(const TimeManager&) = delete;

        /**
         * @brief Get the current time in DS50 format (days since 1950)
         * @return double Current time in DS50 format
         */
        double getCurrentTimeDS50();

        /**
        * @brief Run one iteration of the simulation
        */
        void update();

        std::atomic<double> currentTimeDS50;
        std::atomic<double> simulationTimeDS50;
        std::atomic<float> timeScale;
        std::atomic<int> simulationStep;
        
        std::function<void(double)> callback; // Callback usually set once before running, or needs mutex protection if changed dynamically
        std::thread simulationThread;

        std::atomic<bool> running{false}; // flag indicating if the simulation loop is running
        std::atomic<bool> propagationComplete{false}; // flag indicating if the propagation step is complete (starts false -> satelites are updated -> true)
        std::atomic<bool> renderingComplete{true}; // flag indicating if the rendering step is complete (starts true -> frame is rendered -> false)
        /*
        Control flow: Propagate satellites -> set propagationComplete = true -> main loop sees flag, renders frame -> set renderingComplete = true -> time manager sees flag, continues propagation
        */
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
        void runSimulation(std::function<void(double)> func);

        // Stop the simulation loop, do nothing for now
        void stop() {
            running.store(false);
            if (simulationThread.joinable()) {
                simulationThread.join();
            }
        }

        TaskStatus getPropagationStatus() {
            return propagationComplete.load() ? TaskStatus::COMPLETED : TaskStatus::IN_PROGRESS;
        }

        TaskStatus getRenderingStatus() {
            return renderingComplete.load() ? TaskStatus::COMPLETED : TaskStatus::IN_PROGRESS;
        }

        void setRenderingStatus(TaskStatus status) {
            if (status == TaskStatus::COMPLETED) {
                renderingComplete.store(true);
            } else {
                renderingComplete.store(false);
            }
        }

        void setPropagationStatus(TaskStatus status) {
            if (status == TaskStatus::COMPLETED) {
                propagationComplete.store(true);
            } else {
                propagationComplete.store(false);
            }
        }

        bool isRunning() {
            return running.load();
        }   
        
};

