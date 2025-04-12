# CMakeLists.txt for the unit tests:
# =================================
message(STATUS "unit tests CMakeLists.txt of ${CMAKE_PROJECT_NAME}")
 
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Locate GTest
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
find_library(GTEST_LIBRARY gtest HINTS /usr/lib)
message(STATUS "GTEST_INCLUDE_DIRS is: ${GTEST_INCLUDE_DIRS}")
message(STATUS "GTEST_LIBRARY is: ${GTEST_LIBRARY}")
message(STATUS "GTEST_LIBRARIES is: ${GTEST_LIBRARIES}")

set(unitTestOutName unitTests)
add_executable(${unitTestOutName} main.cpp)
target_link_libraries(${unitTestOutName} ${GTEST_LIBRARY} myLoggerLib pthread)
