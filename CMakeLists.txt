cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)


# Driver options
option(CHAOS_DRIVER_AUDIO "Audio driver" "OpenAL")
option(CHAOS_DRIVER_GRAPHICS "Graphics driver" "D2D")


# ChaosEngine

## Compile
add_library(ChaosEngine STATIC)
set_target_properties(ChaosEngine PROPERTIES OUTPUT_NAME "ChaosEngine")

## Includes
target_include_directories(ChaosEngine
    PUBLIC ChaosEngine/Include
    PRIVATE ChaosEngine/Source
)

## Sources
target_sources(ChaosEngine PRIVATE
    ChaosEngine/Source/Chaos/Core/Base.cpp
)

# Audio drivers
if(CHAOS_DRIVER_AUDIO STREQUAL "OpenAL")
    target_include_directories(ChaosEngine PRIVATE
        ChaosEngine/Drivers/
    )
    target_sources(ChaosEgnien PRIVATE
        ChaosEngine/
    )
endif()


link_libraries(
    "D2D1.lib"
    "glfw3.lib"
    "OpenAL32.lib"
    "sndfile.lib"
)
