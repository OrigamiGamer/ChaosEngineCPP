cmake_minimum_required(VERSION 3.10)

project("GameExample-1" VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(debug "debug.cpp")
set_target_properties(debug PROPERTIES OUTPUT_NAME "debug" SUFFIX ".exe")

find_package(ChaosEngine REQUIRED)
target_link_libraries(debug ChaosEngine)
