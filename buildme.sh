#!/bin/bash

rm -rf build
mkdir build
cd build

# gets the first command-line $1 variable and assign it to USE_CUDA_FLAG
USE_CUDA_FLAG=$1

if [ "$USE_CUDA_FLAG" == "cuda" ]; then
    # cmake: configure the project to the CMakeLists.txt which is in parent directory ..
    # D specifies a variable 
    # DCMAKE_BUILD_TYPE variable CMAKE_BUILD_TYPE (which is keyword in cmake) sets to Debug
    # Debug: for example adds -g (for gdb) and -O0 (no compiler optimization)
    # DUSE_CUDA sets the variable USE_CUDA which is used in CMakeLists.txt (use for cuda support)
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DUSE_CUDA=ON
else
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DUSE_CUDA=OFF
fi

cmake --build . --config Debug
./simpleDNN