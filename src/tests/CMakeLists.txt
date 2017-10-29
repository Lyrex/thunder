cmake_minimum_required(VERSION 3.7)
project(THUNDER_TESTS)

if (WIN32)
    include_directories($ENV{DEV_PATH}/include)
else ()
    find_package(fmt REQUIRED)
    set(FMT_LINK_COMMAND fmt::fmt-header-only)
endif ()

add_executable(filter_accounts filter_accounts.cpp)
add_executable(test_benchmark test_benchmark.cpp)

target_link_libraries(filter_accounts PRIVATE thunder ${FMT_LINK_COMMAND})
target_link_libraries(test_benchmark PRIVATE thunder ${FMT_LINK_COMMAND})
