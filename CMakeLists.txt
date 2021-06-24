cmake_minimum_required(VERSION 3.19)
project(gpu_programming)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third-party/glfw)
add_subdirectory(third-party/gl3w)

include_directories(
        third-party/glfw/include
        ${PROJECT_BINARY_DIR}/third-party/gl3w/include
)

link_directories(
        ${PROJECT_BINARY_DIR}/third-party/glfw/src
        ${PROJECT_BINARY_DIR}/third-party/gl3w/src
)

link_libraries(glfw gl3w)

set(COUNTER 1)
set(NUM_SAMPLES 3)

while(COUNTER LESS_EQUAL NUM_SAMPLES)
    if(${COUNTER} LESS 10)
        set(EXECUTABLE_NAME "sample00${COUNTER}")
    elseif(${COUNTER} LESS 100)
        set(EXECUTABLE_NAME "sample0${COUNTER}")
    else()
        set(EXECUTABLE_NAME "sample${COUNTER}")
    endif()

    file(GLOB SOURCES samples/${EXECUTABLE_NAME}/*.cpp)
    add_executable(${EXECUTABLE_NAME} ${SOURCES})
    MATH(EXPR COUNTER "${COUNTER}+1")
endwhile(COUNTER LESS_EQUAL NUM_SAMPLES)
