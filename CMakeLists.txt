#This is the project's main CMakeLists.txt
#======================================== 
cmake_minimum_required(VERSION 3.28)

project(myLoggerProject)

message(STATUS "main CMakeLists.txt of ${CMAKE_PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

# Add the following compilation settings (flags) globally to ALL targets
# in this project
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include_directories(src)

add_subdirectory(src/logger)

add_subdirectory(src)

add_subdirectory(tests)

