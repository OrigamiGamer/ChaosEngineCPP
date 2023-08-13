cmake_minimum_required(VERSION 3.5)

project(ChaosEngine VERSION 0.1.0 LANGUAGES C CXX)

# Include Directories
include_directories(ChaosEngine)
include_directories(ChaosEngine/lib)

add_library(${PROJECT_NAME} ChaosEngine/ChaosEngine.cpp)

# 3rd Libraries
target_link_libraries(ChaosEngine ChakraCore.lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



#### How to use ####

# Make sure installed CMake

## For Console:
# 1. > cmake --install ..
# 2. > cmake --build ..

## For Visual Studio Code IDE:
# 1. Press Ctrl+Shift+P to open Command Palette, and execute "CMake: Install";
# 2. Then again execute "CMake: Build";

# Finally, copy a backup of "NewGame" folder, rename the project's name to make your game!
