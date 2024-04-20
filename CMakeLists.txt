cmake_minimum_required(VERSION 3.8)

project(ChaosEngine VERSION 0.1.0 LANGUAGES C CXX)

# Include Directories
include_directories(ChaosEngine/lib ChaosEngine/res ChaosEngine ..)

add_library(${PROJECT_NAME} ChaosEngine/ChaosEngine.cpp)

# 3rd Libraries
target_link_libraries(${PROJECT_NAME} ChakraCore.lib)
target_link_libraries(${PROJECT_NAME} OpenAL32.lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
