cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB_RECURSE "SOURCES" "ChaosEngine/*.cpp")
file(GLOB_RECURSE "HEADERS" "ChaosEngine/*.h")
file(GLOB_RECURSE "LIBS" "ChaosEngine/Lib/*.lib")

include_directories(${HEADERS})
link_libraries(${LIBS})



# add_executable(debug "Game/GameExample1/main.cpp")
# set_target_properties(debug PROPERTIES OUTPUT_NAME "debug" SUFFIX ".exe")
