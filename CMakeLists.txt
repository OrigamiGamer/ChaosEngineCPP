cmake_minimum_required(VERSION 3.5)
project(ChaosEngine VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(ChaosEngine/lib)

add_library(ChaosEngine ChaosEngine/ChaosEngine.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
