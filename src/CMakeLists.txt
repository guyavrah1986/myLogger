# CMakeLists.txt file for the main application (executable)
# =========================================================

set(exeName "mainApplication")

message(STATUS "CMakeLists.txt of ${exeName} executable")

# add the executable
add_executable(${exeName} main.cpp)

target_include_directories(${exeName} PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )
                        
target_link_libraries(${exeName} myLoggerLib pthread)
