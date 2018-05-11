cmake_minimum_required(VERSION 2.6)

set(PROJ_NAME SigSlotTest)
project (${PROJ_NAME} LANGUAGES CXX)

include_directories("${CMAKE_SOURCE_DIR}")
aux_source_directory(. SOURCE_DIR)
add_executable(${PROJ_NAME} ${SOURCE_DIR})
target_link_libraries(${PROJ_NAME} CppUnitLite)