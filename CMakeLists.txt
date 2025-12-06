cmake_minimum_required(VERSION 3.10)
project(SatSim)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DCURL_STATICLIB)
set(CMAKE_BUILD_TYPE Debug)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/curl
    ${CMAKE_SOURCE_DIR}/include/rapidjson
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/Services
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/Wrappers
)

# Collect all .cpp files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# SGP4 Wrapper files
set(SGP4_WRAPPERS
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/wrappers/DllMainDll.c
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/wrappers/EnvConstDll.c
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TimeFuncDll.c
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/wrappers/AstroFuncDll.c
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TleDll.c
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/wrappers/Sgp4PropDll.c
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/SampleCode/C/DriverExamples/services/DllUtils.c
)

# Create executable
add_executable(app 
    ${SOURCES}
    ${SGP4_WRAPPERS}
    main.cpp)

# Link libraries
target_link_libraries(app
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/libcurl.lib
        ws2_32.lib
        wldap32.lib
        crypt32.lib
        normaliz.lib
        secur32.lib
        bcrypt.lib
        iphlpapi.lib
)

link_directories(
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/Lib/Windows
)

# Copy SGP4 DLLs to the output directory
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Sgp4Prop/Lib/Windows
    $<TARGET_FILE_DIR:app>
    COMMENT "Copying SGP4 DLLs to output directory"
)
