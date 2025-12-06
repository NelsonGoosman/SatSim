#!/bin/bash

name=Sgp4Prop_Simple

exe_name=${name}
exe_path=./bin

if [[ `uname` == "Darwin" ]]; then
    exe_name=${name}_mac
fi

# Check if LD_LIBRARY_PATH environment variable was set.
if [[ "$LD_LIBRARY_PATH" == "" ]]; then
    echo Please ensure LD_LIBRARY_PATH environment variable is set to your Astrodynamics Standards libraries 
    echo For example export LD_LIBRARY_PATH=../../../../Lib/Linux/IFORT
    exit 1
fi

# Create subdirectories used by makefile
mkdir -p bin
mkdir -p output

# compile all source code
# note: the makefile copies the executable to the bin directory
echo Compiling
make

if [[ "$?" != 0 ]]; then
    echo "Error compiling code"
    exit 1
fi

if [[ `uname` == "Darwin" ]]; then
    install_name_tool -add_rpath "$LD_LIBRARY_PATH" bin/$exe_name
fi

echo Running example
bin/$exe_name

exitCode="$?"

if [[ "$exitCode" != 0 ]]; then
    echo "Error executing $exe_name with exit code of: $exitCode"
    exit 1
fi
