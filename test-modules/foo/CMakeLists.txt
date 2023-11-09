cmake_minimum_required(VERSION 3.22.1)

project(foo)

add_library(foo_tests SHARED foo.cpp)
target_link_libraries(foo_tests Catch2::Catch2)

install(TARGETS foo_tests DESTINATION .)