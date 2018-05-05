cmake_minimum_required(VERSION 2.6)

set(PROJ_NAME SigSlotTest)
project (${PROJ_NAME} LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(${PROJ_NAME} test.cpp)