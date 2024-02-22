cmake_minimum_required(VERSION 3.5)

# Set your Game's Name instead of <NewGame> only in parameters of project
project(NewGame VERSION 0.1.0 LANGUAGES C CXX)

link_directories(../build/x64-Debug)
# include_directories(.)
# include_directories(../ChaosEngine)
# include_directories(../ChaosEngine/lib)
include_directories(. ../ChaosEngine ../ChaosEngine/lib ../ChaosEngine/res)

add_executable(${PROJECT_NAME} WIN32 NewGame.cpp)
target_link_libraries(${PROJECT_NAME} ChaosEngine.lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
