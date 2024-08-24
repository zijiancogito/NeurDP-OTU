cmake_minimum_required(VERSION 3.10)

project(code VERSION 1.0)

configure_file(CodeConfig.h.in CodeConfig.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(options)
add_subdirectory(code)

add_executable(debugall opsequence.cpp)

target_link_libraries(debugall PUBLIC Aarch64Asm Ir Code gflags)

target_include_directories(debugall PUBLIC 
       "${PROJECT_BINARY_DIR}"
       "${PROJECT_SOURCE_DIR}/options"
       )

