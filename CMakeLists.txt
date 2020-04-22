cmake_minimum_required(VERSION 3.17)

project(ResampleDemo VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(resampler
  GIT_REPOSITORY https://github.com/terrygta/SignalResampler.git
  GIT_TAG        9b43aba322bbfe77d5a9b5ca4adb8aa195c3c0fb
)

FetchContent_GetProperties(resampler)
if(NOT resampler_POPULATED)
  FetchContent_Populate(resampler)
endif()


add_library(Resampler
    ${resampler_SOURCE_DIR}/src/resample.cpp
    ${resampler_SOURCE_DIR}/src/resample.h
)

add_executable(ResampleDemo ResampleDemo.cpp)

target_include_directories(ResampleDemo PRIVATE
    $<BUILD_INTERFACE:${resampler_SOURCE_DIR}/src/>
)

target_compile_options(ResampleDemo PUBLIC -std=c++11 -fpermissive -w -Wall)

target_link_libraries(ResampleDemo Resampler)
