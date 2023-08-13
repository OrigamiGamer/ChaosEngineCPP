cmake_minimum_required(VERSION 3.5)
project(NewGame VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# target_link_libraries(ChaosEngineLib ../build/Debug/ChaosEngine.lib)
include_directories(../ChaosEngine)

set(PROJECT_NAME NewGame)

add_executable(${PROJECT_NAME} NewGame.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
