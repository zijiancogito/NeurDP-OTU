set(INC_DIR /usr/include)  
set(LINK_DIR /usr/lib)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_library(Code code.cpp)
target_include_directories(Code PUBLIC
       "$(CMAKE_CURRENT_SOURCE_DIR)"
       "${PROJECT_SOURCE_DIR}/options"
       )
target_link_libraries(Code PUBLIC jsoncpp)


add_library(Aarch64real aarch64real.cpp)
target_include_directories(Aarch64real PUBLIC 
       "$(CMAKE_CURRENT_SOURCE_DIR)"
       "${PROJECT_SOURCE_DIR}/options"
       )
target_link_libraries(Aarch64real PUBLIC jsoncpp Code)

add_library(Aarch64Asm aarch64Asm.cpp)
target_include_directories(Aarch64Asm PUBLIC 
       "$(CMAKE_CURRENT_SOURCE_DIR)"
       "${PROJECT_SOURCE_DIR}/options"
       )
target_link_libraries(Aarch64Asm PUBLIC jsoncpp Code)

add_library(Ir Ir.cpp)
target_include_directories(Ir PUBLIC 
       "$(CMAKE_CURRENT_SOURCE_DIR)"
       "${PROJECT_SOURCE_DIR}/options"
       )
target_link_libraries(Ir PUBLIC jsoncpp Code)