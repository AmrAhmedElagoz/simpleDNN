cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(simpleDNN CXX)

# enable CUDA support, defaults to ON (doesn't really matter as it sets from buildme.sh)
option(USE_CUDA "Enable CUDA for GPU acceleration" ON)


FILE(GLOB_RECURSE SOURCES src/*.cpp)

if(USE_CUDA)
    enable_language(CUDA)
    FILE(GLOB_RECURSE CUDA_SOURCES src/*.cu)
    list(APPEND SOURCES ${CUDA_SOURCES})
    message(STATUS "Building with CUDA support")
    # adding a compiler definition (it will be a preprocessor that can be used in code with #ifdef)
    add_definitions(-DUSE_CUDA)
    set(CMAKE_CUDA_ARCHITECTURES 86)
endif()

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

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
    add_definitions(-D_DEBUG)
endif()

# if("${CMAKE_PROJECT_NAME}" STREQUAL "Debug")
#     # add_compile_definitions(-D_DEBUG)
#     message(STATUS "Building in Debug...")
#     target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _DEBUG)
#     target_compile_options(add PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -G>)
# endif()