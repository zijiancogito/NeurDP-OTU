
add_library(RemoveASM removeASM.cpp)
target_include_directories(RemoveASM PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))


add_library(RemoveIR removeIR.cpp)
target_include_directories(RemoveIR PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))

