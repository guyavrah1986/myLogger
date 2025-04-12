#This is the project's main CMakeLists.txt
#======================================== 
cmake_minimum_required(VERSION 3.28)

project(myLoggerProject)

message(STATUS "main CMakeLists.txt of ${CMAKE_PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_subdirectory(src/logger)

add_subdirectory(tests)

