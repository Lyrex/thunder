cmake_minimum_required(VERSION 3.7)
project(THUNDER_TESTS)

if (WIN32)
    include_directories($ENV{DEV_PATH}/include)
else ()
    find_package(fmt REQUIRED)
    set(FMT_LINK_COMMAND fmt::fmt-header-only)
endif ()

find_program(
        CLANG_TIDY_EXE
        NAMES
        clang-tidy
        clang-tidy-5.0
        clang-tidy-4.0
        clang-tidy-3.9
        clang-tidy-3.8
        clang-tidy-3.7
        clang-tidy-3.6
        clang-tidy-3.5
        DOC "Path to clang-tidy executable"
)

if (NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else ()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-header-filter='.*' -checks='*,-clang-analyzer-alpha.*'")
endif ()

add_executable(filter_accounts filter_accounts.cpp)
add_executable(test_benchmark test_benchmark.cpp)

target_link_libraries(filter_accounts PRIVATE thunder ${FMT_LINK_COMMAND})
target_link_libraries(test_benchmark PRIVATE thunder ${FMT_LINK_COMMAND})

if (CLANG_TIDY_EXE)
    set_target_properties(
            filter_accounts PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )

    set_target_properties(
            test_benchmark PROPERTIES
            CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif ()
