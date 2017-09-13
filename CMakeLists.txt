cmake_minimum_required(VERSION 3.8)
project(thunder)

add_library(thunder INTERFACE)
target_include_directories(thunder INTERFACE thunder/include/)

add_subdirectory(thunder/tests)