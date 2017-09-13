cmake_minimum_required(VERSION 3.8)
project(THUNDER_TESTS)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

include_directories($ENV{DEV_PATH}/include)

set(CLANG_TIDY_EXE "C:/Program Files (x86)/LLVM/bin/clang-tidy.exe")

if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(filter_accounts filter_accounts.cpp)
add_executable(test_benchmark test_benchmark.cpp)

target_link_libraries(filter_accounts thunder)
target_link_libraries(test_benchmark thunder)

if(CLANG_TIDY_EXE)
    set_target_properties(
            filter_accounts PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )

    set_target_properties(
            test_benchmark PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif()