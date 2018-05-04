cmake_minimum_required(VERSION 2.6)

set(PROJ_NAME SigSlotTest)
project (${PROJ_NAME} LANGUAGES CXX)

add_compile_options(-std=c++11)
add_executable(${PROJ_NAME} test.cpp)