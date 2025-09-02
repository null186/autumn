cmake_minimum_required(VERSION 3.15.4)
project(AutumnLog)
set(CMAKE_CXX_STANDARD 17)

add_definitions(
        -O3 -g -W -Wall
)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

aux_source_directory(${PROJECT_SOURCE_DIR}/src AUTUMN_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/task AUTUMN_SRC_TASK)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/utils AUTUMN_SRC_UTILS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/writer AUTUMN_SRC_WRITER)

add_library(autumn_shared SHARED ${AUTUMN_SRC} ${AUTUMN_SRC_TASK} ${AUTUMN_SRC_UTILS} ${AUTUMN_SRC_WRITER})
add_library(autumn_static STATIC ${AUTUMN_SRC} ${AUTUMN_SRC_TASK} ${AUTUMN_SRC_UTILS} ${AUTUMN_SRC_WRITER})

set_target_properties(autumn_shared PROPERTIES OUTPUT_NAME "include/autumn")
get_target_property(OUTPUT_VALUE autumn_shared OUTPUT_NAME)
message(STATUS "This is the autumn_shared OUTPUT_NAME: " ${OUTPUT_VALUE})

set_target_properties(autumn_static PROPERTIES OUTPUT_NAME "include/autumn")
get_target_property(OUTPUT_VALUE autumn_static OUTPUT_NAME)
message(STATUS "This is the autumn_static OUTPUT_NAME: " ${OUTPUT_VALUE})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
link_directories(${LIBRARY_OUTPUT_PATH})

# 链接静态库，在 add_executable 之前
link_libraries(autumn_static)

set(SRC demo/main.cpp)
add_executable(AutumnLog ${SRC})

# 链接动态库，在 add_executable 之后
# target_link_libraries(AutumnLog "autumn_shared")
