#pragma once
#include <string>
#include <functional>
#include <iostream>
#include "tle.h"

enum class SatelliteClassification {
   STARLINK, 
   OTHER,
   UNKNOWN
};


// The main struct representing a single satellite object in the simulation.
struct Entity {
    long long id;                         // The unique ID within the sim
    std::string name;                        // Common name 

    // Graphics Data
    SatelliteClassification classification;  // Type of Entity (Payload, Debris, etc.)
    bool is_active = true;                   // Sim activity flag
    
    // TLE Data
    TleData tle;                             // The constant orbital elements
    
    // Current State 
    double current_state[3];               // Current position and velocity (ECI)
    double last_propagation_time = 0.0;      // Simulation time of the last update
};


