cmake_minimum_required(VERSION 3.31)
project(dsp_learning)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

include_directories(biquad-filter)

#add_executable(dsp_learning biquad-filter/biquad_filter.cpp)
add_executable(dsp_learning sine-wave-generation/sine_wave.cpp)
