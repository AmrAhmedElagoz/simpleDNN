#!/bin/bash

rm -rf build
mkdir build
cd build

# Check if CUDA flag is passed as an argument to the script
USE_CUDA_FLAG=$1

# Set the CUDA option for CMake based on the passed argument
if [ "$USE_CUDA_FLAG" == "cuda" ]; then
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DUSE_CUDA=ON
else
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DUSE_CUDA=OFF
fi

cmake --build . --config Debug
./simpleDNN