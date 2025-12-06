# C++ Orbital Simulation - Project Structure

## Directory Tree

```
src/
├── main.cpp                # Application entry point
├── core/                   # Central management and orchestration
│   ├── Simulation.cpp      # Main simulation loop and thread management
│   ├── TimeManager.h       # Simulation clock, time scaling, and epoch handling
│   └── Config.h            # Global constants and configuration settings
├── physics/                # Mathematical and orbital logic
│   ├── Propagator.cpp      # SGP4 implementation for TLE propagation
│   ├── CollisionSystem.cpp # Spatial partitioning (Octree) and collision checks
│   └── OrbitalMath.h       # Coordinate conversions (ECI, ECEF, LLA)
├── data/                   # Data ingestion and storage
│   ├── Satellite.h         # Data structure for satellite objects
│   ├── SpaceTrackAPI.cpp   # Network handling for fetching TLEs
│   └── TLEParser.cpp       # Parsing logic for TLE/OMM formats
└── graphics/               # Rendering and Visualization
    ├── Renderer.cpp        # OpenGL context and instanced rendering logic
    ├── EarthModel.cpp      # Texture handling and atmospheric shaders
    ├── Camera.cpp          # View matrix controls
    └── GUI.cpp             # ImGui overlay implementation
```

## Module Descriptions

### Root (src/)
- **main.cpp**: The entry point. It initializes the separate threads (Physics Thread vs. Render Thread), sets up the window context (GLFW), and starts the main event loop.

### Core (src/core/)
- **Simulation.cpp**: The "brain" of the application. It ensures thread safety when swapping buffers between the physics engine and the renderer.
- **TimeManager.h**: Handles the complex task of coordinating "Wall Clock" time with "Simulation Time." It manages the GMST (Greenwich Mean Sidereal Time) calculations required for Earth rotation.
- **Config.h**: A central registry for settings like MAX_SATELLITES, G_FORCE_CONSTANTS, and default API endpoints.

### Physics (src/physics/)
- **Propagator.cpp**: Wraps the SGP4 algorithm. This module takes a TLE and a timestamp and returns a position/velocity vector.
- **CollisionSystem.cpp**: Implements a Dynamic Octree. It partitions 3D space to allow for efficient nearest-neighbor queries without checking every satellite against every other ($O(N \log N)$ instead of $O(N^2)$).
- **OrbitalMath.h**: Helper functions for vector math, specifically converting between Earth-Centered Inertial (ECI) frames used by physics and Earth-Centered Earth-Fixed (ECEF) frames used for rendering relative to the ground.

### Data (src/data/)
- **Satellite.h**: Defines the Satellite struct, which holds the orbital elements, unique ID, current position, and classification (Debris, Payload, Rocket Body).
- **SpaceTrackAPI.cpp**: Manages HTTP requests using libcurl or cpr. It handles authentication with Space-Track.org.
- **TLEParser.cpp**: String processing utilities to extract orbital elements from the raw 3-line text format or JSON OMMs.

### Graphics (src/graphics/)
- **Renderer.cpp**: Manages Vertex Buffer Objects (VBOs) and Shader Programs. It is responsible for the "Instanced Rendering" call that draws thousands of dots in a single GPU command.
- **EarthModel.cpp**: Manages the high-resolution textures for the Earth and the shader logic for the day/night cycle and atmosphere.
- **Camera.cpp**: Handles user input to move the view matrix (Zoom, Pan, Orbit).
- **GUI.cpp**: Implementation of the Dear ImGui overlay, allowing users to filter satellites and speed up time.