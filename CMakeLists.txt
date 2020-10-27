cmake_minimum_required(VERSION 3.9)
project(iz2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -O3 -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(INC_DIR ${DIR}/project/include)
set(SRC_DIR ${DIR}/project/src)
set(TESTS_DIR ${DIR}/project/tests)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(project/include)

# статическая библиотека ST_CALCULATE_TEMPERATURE_JUMP
add_library(ST_CALCULATE_TEMPERATURE_JUMP STATIC
        ${INC_DIR}/utils.h
        ${SRC_DIR}/utils.c
        ${SRC_DIR}/ST/ST_calculate_temperature_jump.c
        ${INC_DIR}/ST/ST_temperature_jump.h)

# динамическая библиотека MT_CALCULATE_TEMPERATURE_JUMP
add_library(MT_CALCULATE_TEMPERATURE_JUMP SHARED
        ${INC_DIR}/utils.h
        ${SRC_DIR}/utils.c
        ${SRC_DIR}/MT/MT_calculate_temperature_jump.c
        ${INC_DIR}/MT/MT_temperature_jump.h)

# таргет tests
add_executable(tests ${TESTS_DIR}/main.cpp)
target_include_directories(tests PUBLIC ${INC_DIR})
target_link_libraries(tests
        ${GTEST_LIBRARIES}
        Threads::Threads
        pthread
        ST_CALCULATE_TEMPERATURE_JUMP
        MT_CALCULATE_TEMPERATURE_JUMP)
enable_testing()

# таргет iz2
add_executable(iz2 ${SRC_DIR}/main.c)
target_include_directories(iz2 PUBLIC ${INC_DIR})
target_link_libraries(iz2
        ${GTEST_LIBRARIES}
        Threads::Threads
        pthread
        ST_CALCULATE_TEMPERATURE_JUMP
        MT_CALCULATE_TEMPERATURE_JUMP)

