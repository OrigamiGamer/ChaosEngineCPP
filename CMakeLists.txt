cmake_minimum_required(VERSION 3.8)

project(ChaosEngine VERSION 0.1.0 LANGUAGES C CXX)

# Directories
set(PATH ChaosEngine/lib ChaosEngine/res ChaosEngine .)
link_directories(${PATH})
include_directories(${PATH})

add_library(${PROJECT_NAME} ChaosEngine/ChaosEngine.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
