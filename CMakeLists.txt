cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)



###### Driver Options ######

option(CHAOS_DRIVER_AUDIO "Audio driver" "OpenAL")
option(CHAOS_DRIVER_PLATFORM "Platform driver" "Win32")
option(CHAOS_DRIVER_GRAPHICS "Graphics driver" "D2D")



###### ChaosEngine ######

# compile
add_library(ChaosEngine STATIC)
set_target_properties(ChaosEngine PROPERTIES OUTPUT_NAME "ChaosEngine")

# includes
target_include_directories(ChaosEngine
    PUBLIC ChaosEngine/Engine/Include
    PRIVATE ChaosEngine/Engine/Source
)

# sources
target_sources(ChaosEngine PRIVATE
    ChaosEngine/Engine/Source/Core/Base.cpp
)

# link directories
link_directories(ChaosEngine/Dependences/Lib)



###### Audio ######

# OpenAL
if(CHAOS_DRIVER_AUDIO STREQUAL "OpenAL")
    target_include_directories(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Audio/OpenAL/Include
    )
    target_sources(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Audio/OpenAL/Source/Source.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        OpenAL32.lib
        sndfile.lib
    )
endif()



###### Graphics ######

# Win32
if(CHAOS_DRIVER_PLATFORM STREQUAL "Win32")
    # D2D
    if(CHAOS_DRIVER_GRAPHICS STREQUAL "D2D")
        target_include_directories(ChaosEngine PRIVATE
            ChaosEngine/Drivers/Graphics/D2D/Include
        )
        target_sources(ChaosEngine PRIVATE
            # ChaosEngine/Drivers/Graphics/D2D/Source/D2D.cpp
        )
        target_link_libraries(ChaosEngine PRIVATE
            D2D1.lib
        )
    endif()
endif()



###### Platform ######

# Win32
if(CHAOS_DRIVER_PLATFORM STREQUAL "Win32")
    target_include_directories(ChaosEngine PRIVATE
        ChaosEngine/Drivers/Platform/Win32/Include
    )
    target_sources(ChaosEngine PRIVATE
        # ChaosEngine/Drivers/Platform/Source/Win32.cpp
    )
    target_link_libraries(ChaosEngine PRIVATE
        glfw3.lib
    )
endif()




# link_libraries(
#     "D2D1.lib"
#     "glfw3.lib"
#     "OpenAL32.lib"
#     "sndfile.lib"
# )
