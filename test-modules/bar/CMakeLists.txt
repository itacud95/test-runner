cmake_minimum_required(VERSION 3.22.1)

project(bar)

add_library(bar_tests SHARED bar.cpp)
target_link_libraries(bar_tests Catch2::Catch2)
