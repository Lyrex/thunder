cmake_minimum_required(VERSION 3.7)
project(thunder)

add_library(thunder INTERFACE)
target_compile_definitions(thunder INTERFACE LIBRARY_HEADER_ONLY)
target_compile_features(thunder INTERFACE cxx_auto_type cxx_constexpr cxx_aggregate_default_initializers
        cxx_defaulted_functions cxx_defaulted_move_initializers cxx_lambdas cxx_lambda_init_captures
        cxx_generic_lambdas cxx_generalized_initializers cxx_nullptr)
target_include_directories(thunder INTERFACE include/)

add_subdirectory(tests)
