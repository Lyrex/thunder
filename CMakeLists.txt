cmake_minimum_required(VERSION 3.8)
project(thunder)

add_library(thunder INTERFACE)
target_compile_definitions(thunder INTERFACE LIBRARY_HEADER_ONLY)
target_include_directories(thunder INTERFACE include/)

add_subdirectory(tests)