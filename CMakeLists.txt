cmake_minimum_required(VERSION 3.7)
project(libthunder)

include(GNUInstallDirs)

add_library(thunder INTERFACE)
		
target_include_directories(thunder PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
		
# target_include_directories(thunder INTERFACE  
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/thunder>  
#     $<INSTALL_INTERFACE:include/thunder>
# )		
# target_include_directories(thunder INTERFACE include/)

target_compile_definitions(thunder INTERFACE LIBRARY_HEADER_ONLY)
target_compile_features(thunder INTERFACE cxx_auto_type cxx_constexpr cxx_aggregate_default_initializers
        cxx_defaulted_functions cxx_defaulted_move_initializers cxx_lambdas cxx_lambda_init_captures
        cxx_generic_lambdas cxx_generalized_initializers cxx_nullptr)

install(TARGETS thunder EXPORT ThunderConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ThunderConfig
  NAMESPACE thunder::
  DESTINATION lib/cmake/thunder
)


export(TARGETS thunder FILE MyLibraryConfig.cmake)