# CMakeLists.txt file for the logger library
# ==========================================

set(loggerLibName "myLoggerLib")

message(STATUS "CMakeLists.txt of ${loggerLibName} library")

add_library(${loggerLibName} SHARED fileLogger.cpp memoryLogger.cpp) #basicLogger.cpp

target_compile_options(${loggerLibName} PUBLIC -g -O0 -Wall -fprofile-arcs -ftest-coverage)
target_link_options(${loggerLibName} PUBLIC -fprofile-arcs -ftest-coverage)

message(STATUS "CMakeLists.txt of ${loggerLibName} - created library")