cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# includes

set(INCLUDE_LIST
    .
    "ChaosEngine"
    "ChaosEngine/Device"
    "ChaosEngine/Graphic"
    "ChaosEngine/Audio"
    "ChaosEngine/Content"
    "ChaosEngine/Lib"
)
include_directories(${INCLUDE_LIST})

# libraries

set(LINK_LIST
    .
    "ChaosEngine/Lib"
)
link_directories(${LINK_LIST})

link_libraries("D2D1.lib" "libglfw3.a")




# file(GLOB_RECURSE "SOURCES" "ChaosEngine/*.cpp")
# file(GLOB_RECURSE "HEADERS" "ChaosEngine/*.h")
