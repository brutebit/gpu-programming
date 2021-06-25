cmake_minimum_required(VERSION 3.19)
project(gpu_programming)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third-party/glfw)
add_subdirectory(third-party/gl3w)

if(NOT EXISTS "${PROJECT_BINARY_DIR}/third-party/gl3w/src/gl3w.c")
    # find a way to execute make in "${PROJECT_BINARY_DIR}/third-party/gl3w" without problems
endif()

include_directories(
        third-party/glfw/include
        ${PROJECT_BINARY_DIR}/third-party/gl3w/include
)

link_directories(
        ${PROJECT_BINARY_DIR}/third-party/glfw/src
        ${PROJECT_BINARY_DIR}/third-party/gl3w/src
)

link_libraries(glfw gl3w)

file(GLOB SAMPLES samples/*)
foreach(SAMPLE ${SAMPLES})
    string(REPLACE "${PROJECT_SOURCE_DIR}/samples/" "" EXECUTABLE_NAME ${SAMPLE})
    file(GLOB SOURCES ${SAMPLE}/*.cpp)
    add_executable(${EXECUTABLE_NAME} ${SOURCES})
endforeach(SAMPLE ${SAMPLES})
