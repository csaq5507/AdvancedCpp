cmake_minimum_required(VERSION 3.5)

project(Exercise3)

include(CTest)

enable_testing()

# Link runTests with what we want to test and the GTest and pthread library
aux_source_directory(. SRC_LIST)
aux_source_directory(task1 SRC_LIST)

add_executable(task1 task1/main.cpp)

add_executable(task2 task2/main.cpp)
add_executable(task5 task5/bubble_sort.c)