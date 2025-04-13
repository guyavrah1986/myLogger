# CMakeLists.txt file for the utils library
# ==========================================

set(utilsLibName "myUtilsLib")

message(STATUS "CMakeLists.txt of ${utilsLibName} library")

add_library(${utilsLibName} SHARED utils.cpp)

target_compile_options(${utilsLibName} PUBLIC -g -O0 -Wall -fprofile-arcs -ftest-coverage)
target_link_options(${utilsLibName} PUBLIC -fprofile-arcs -ftest-coverage)

message(STATUS "CMakeLists.txt of ${utilsLibName} - created library")