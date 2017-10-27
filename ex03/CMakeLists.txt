cmake_minimum_required(VERSION 3.6)

project(Exercise2)

include(CTest)

enable_testing()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE (CPPexperimental)
IF(DL_FOUND AND CPPEXPERIMENTAL_FOUND)
    SET (LIBRARIES ${LIBRARIES}
            ${DL_LIBRARIES} ${CPPEXPERIMENTAL_LIBRARIES})
    INCLUDE_DIRECTORIES (${DL_INCLUDE_DIRS})
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_DL=YES")
ENDIF()

# Link runTests with what we want to test and the GTest and pthread library
aux_source_directory(. SRC_LIST)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/)


add_executable(${PROJECT_NAME} Source.cpp)
add_library(library ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} library stdc++fs)
