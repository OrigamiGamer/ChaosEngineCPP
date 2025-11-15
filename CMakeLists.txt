cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)



# includes

set(INCLUDE_LIST
    .
    "ChaosEngine"
)
include_directories(${INCLUDE_LIST})



# libraries

set(LINK_LIST
    .
    "ChaosEngine/ExternalLibrary"
)
link_directories(${LINK_LIST})

link_libraries(
    "D2D1.lib"
    "glfw3.lib"
    "OpenAL32.lib"
    "sndfile.lib"
)



# compile

add_library(ChaosEngine_Static STATIC "ChaosEngine/Source/Source.cpp")
set_target_properties(ChaosEngine_Static PROPERTIES OUTPUT_NAME "ChaosEngine" SUFFIX ".lib")





# file(GLOB_RECURSE "SOURCES" "ChaosEngine/*.cpp")
# file(GLOB_RECURSE "HEADERS" "ChaosEngine/*.h")
