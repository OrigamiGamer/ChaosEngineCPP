cmake_minimum_required(VERSION 3.10)

project(ChaosEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)


set(INCLUDE_LIST 
	.
	"ChaosEngine"
	"ChaosEngine/PhysicsEngine"
	"basic_chaos_engine"
	"basic_chaos_engine/libraries"
	"basic_chaos_engine/libraries/utils"
	"basic_chaos_engine/libraries/utils/fftw3/api"
	"basic_chaos_engine/libraries/audio"
	"basic_chaos_engine/libraries/audio/libsndfile"
	"basic_chaos_engine/libraries/audio/OpenAL"
	"basic_chaos_engine/libraries/graphics"
	"basic_chaos_engine/libraries/graphics/DirectX"
	"basic_chaos_engine/libraries/graphics/DirectX/D2D"
)
set(LINK_LIST "libraries")

include_directories(${INCLUDE_LIST})
link_directories(${LINK_LIST})


add_library(engine_shared SHARED "chaos_engine.cpp")
set_target_properties(engine_shared PROPERTIES SUFFIX ".dll")
set_target_properties(engine_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_Shared CLEAN_DIRECT_OUTPUT 1)

add_library(engine_static STATIC "chaos_engine.cpp")
set_target_properties(engine_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_Static)

# add_executable(debug "chaos_engine.cpp")