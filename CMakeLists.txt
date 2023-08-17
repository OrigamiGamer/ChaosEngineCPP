cmake_minimum_required(VERSION 3.5)

project(ChaosEngine VERSION 0.1.0 LANGUAGES C CXX)

# Include Directories
include_directories(ChaosEngine)
include_directories(ChaosEngine/lib)
include_directories(ChaosEngine/res)

add_library(${PROJECT_NAME} ChaosEngine/ChaosEngine.cpp)

# 3rd Libraries
target_link_libraries(ChaosEngine ChakraCore.lib)
target_link_libraries(ChaosEngine fmodstudio_vc_x64.lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
