project(GTest)

cmake_minimum_required(VERSION 2.8)
 
ADD_DEFINITIONS(
    -std=c++14
    -Wall
    -Wextra
)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
