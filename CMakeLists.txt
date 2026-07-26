cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)



###### Driver Options ######

### Supported Drivers:
# Audio: OpenAL | ...
# Graphics: D2D | ...
# Platform: Win32 | ...
option(CHAOS_DRIVER_AUDIO "Audio driver" "OpenAL")
option(CHAOS_DRIVER_GRAPHICS "Graphics driver" "D2D")
option(CHAOS_DRIVER_PLATFORM "Platform driver" "Win32")



###### ChaosEngine ######

# target information
add_library(ChaosEngine STATIC)
set_target_properties(ChaosEngine PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# include directories
target_include_directories(ChaosEngine
    PUBLIC ChaosEngine
)

# source directories
target_sources(ChaosEngine PRIVATE
    ChaosEngine/Engine/Source/Core/Base.cpp
)

# link directories
link_directories(ChaosEngine/Dependences/Lib)



###### Audio ######

# OpenAL
if(CHAOS_DRIVER_AUDIO STREQUAL "OpenAL")
    target_sources(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Source/Audio/OpenAL/Buffer.cpp
        ChaosEngine/Drivers/Source/Audio/OpenAL/Source.cpp
        ChaosEngine/Drivers/Source/Audio/OpenAL/AudioEngine.cpp
        ChaosEngine/Drivers/Source/Audio/OpenAL/AudioPlayer.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        OpenAL32.lib
        sndfile.lib
    )
endif()



###### Graphics ######

# D2D
if(CHAOS_DRIVER_GRAPHICS STREQUAL "D2D")
    target_sources(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Source/Graphics/D2D/D2D.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        D2D1.lib
    )
endif()



###### Platform ######

# Win32
if(CHAOS_DRIVER_PLATFORM STREQUAL "Win32")
    target_sources(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Source/Platform/Win32/Win32.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        glfw3.lib
    )
endif()
