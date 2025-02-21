cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

# Set the project name and the C++ standard
project(simpleDNN CXX)

# Option to enable CUDA support
option(USE_CUDA "Enable CUDA for GPU acceleration" ON)

# Automatically gather source files
FILE(GLOB_RECURSE SOURCES src/*.cpp)

if(USE_CUDA)
    enable_language(CUDA)
    FILE(GLOB_RECURSE CUDA_SOURCES src/*.cu)
    list(APPEND SOURCES ${CUDA_SOURCES})
    message(STATUS "Building with CUDA support")
    add_definitions(-DUSE_CUDA)
    set(CMAKE_CUDA_ARCHITECTURES 86)
endif()

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link CUDA libraries if CUDA is enabled
if(USE_CUDA)
    target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES})
endif()

# Set C++ standard to 20
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if(USE_CUDA)
    # Set CUDA standard and properties if CUDA is enabled
    set_property(TARGET ${PROJECT_NAME} PROPERTY CUDA_STANDARD 11)
    set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
endif()
