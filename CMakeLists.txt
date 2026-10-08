cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)



###### ChaosEngine ######

# target information
add_library(ChaosEngine STATIC)
set_target_properties(ChaosEngine PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# link directories
link_directories(ChaosEngine/Dependences/Lib)

# include directories
target_include_directories(ChaosEngine
    PUBLIC ChaosEngine
)



###### Engine ######

# source directories
target_sources(ChaosEngine PRIVATE
    ChaosEngine/Engine/Source/Core/Base.cpp
    ChaosEngine/Engine/Source/Core/String.cpp
)



###### Audio ######

# OpenAL
target_sources(ChaosEngine PRIVATE
    ChaosEngine/Drivers/Source/Audio/OpenAL/Buffer.cpp
    ChaosEngine/Drivers/Source/Audio/OpenAL/Source.cpp
    ChaosEngine/Drivers/Source/Audio/OpenAL/Device.cpp
    ChaosEngine/Drivers/Source/Audio/OpenAL/Context.cpp
    ChaosEngine/Drivers/Source/Audio/OpenAL/Listener.cpp
)
target_link_libraries(ChaosEngine PRIVATE
    OpenAL32.lib
    sndfile.lib
)



###### Graphics ######

# D2D
target_sources(ChaosEngine PRIVATE
    ChaosEngine/Drivers/Source/Graphics/D2D/D2D.cpp
)
target_link_libraries(ChaosEngine PRIVATE
    D2D1.lib
)



###### Windows ######

# win32 and glfw
target_sources(ChaosEngine PRIVATE
    ChaosEngine/Drivers/Source/Platform/Win32/Win32.cpp
)
target_link_libraries(ChaosEngine PRIVATE
    glfw3.lib
)
