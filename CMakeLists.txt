cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

if(WIN32)
    message(STATUS "Building for Windows....")
endif()

project(simpleDNN)

FILE(GLOB_RECURSE SOURCES src/*.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)