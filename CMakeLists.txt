cmake_minimum_required(VERSION 3.22.1)

project("test-runner")

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# catch
option(BUILD_SHARED_LIBS "Build shared library" on)
add_subdirectory(Catch2-3.4.0)

# test-modules libraries 
add_subdirectory(test-modules)

# test_runner library
add_library(test_runner SHARED test_runner.cpp)
target_link_libraries(test_runner
    Catch2::Catch2WithMain
)

# main executable
add_executable(main main.cpp)
target_link_libraries(main test_runner)
