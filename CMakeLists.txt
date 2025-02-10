cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


set(INCLUDE_LIST
    .
    "ChaosEngine"
    "ChaosEngine/Device"
    "ChaosEngine/Graphic"
    "ChaosEngine/Audio"
    "ChaosEngine/Content"
    "ChaosEngine/Lib"
)
set(LINK_LIST
    .
    "ChaosEngine/Lib"
)
include_directories(${INCLUDE_LIST})
link_directories(${LINK_LIST})


# add_library(engine_shared SHARED "ChaosEngine.cpp")
# set_target_properties(engine_shared PROPERTIES SUFFIX ".dll")
# set_target_properties(engine_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_Shared CLEAN_DIRECT_OUTPUT 1)

# add_library(engine_static STATIC "ChaosEngine.cpp")
# set_target_properties(engine_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_Static)

link_libraries("D2D1.lib" "libglfw3.a")

add_executable(debug "debug.cpp")
set_target_properties(debug PROPERTIES OUTPUT_NAME "debug" SUFFIX ".exe")
