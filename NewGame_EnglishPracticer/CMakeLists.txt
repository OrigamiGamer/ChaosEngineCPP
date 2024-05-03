cmake_minimum_required(VERSION 3.8)
project(NewGame VERSION 0.1.0 LANGUAGES C CXX)

set(PATH ../ChaosEngine/lib ../ChaosEngine/res ../ChaosEngine .. .)
link_directories(../build/x64-Debug ../build/Debug ${PATH})
include_directories(${PATH})

add_executable(${PROJECT_NAME} WIN32 NewGame.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
