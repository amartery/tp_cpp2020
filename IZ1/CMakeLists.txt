cmake_minimum_required(VERSION 3.9)
project(iz1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/project")

set(INC_DIR ${DIR}/project/include)
set(SRC_DIR ${DIR}/project/src)
set(TESTS_DIR ${DIR}/project/tests)



add_executable(iz1
        ${SRC_DIR}/main.c
        ${INC_DIR}/matrix.h
        ${SRC_DIR}/matrix.c)

target_include_directories(iz1 PUBLIC ${INC_DIR})

add_executable(tests
        ${INC_DIR}/matrix.h
        ${SRC_DIR}/matrix.c
        ${TESTS_DIR}/main.cpp)

target_include_directories(tests PUBLIC ${INC_DIR})


target_link_libraries(tests ${GTEST_LIBRARIES} Threads::Threads)

enable_testing()

add_test(NAME tests COMMAND tests WORKING_DIRECTORY ${DIR}/project/tests/data)
