cmake_minimum_required(VERSION 3.6)

project(VCS)


# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${PROJECT_SOURCE_DIR}/cmake)

set(BENCHMARK_ENABLE_TESTING OFF)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE (CPPexperimental)
IF(DL_FOUND AND CPPEXPERIMENTAL_FOUND)
    SET (LIBRARIES ${LIBRARIES}
            ${DL_LIBRARIES} ${CPPEXPERIMENTAL_LIBRARIES})
    INCLUDE_DIRECTORIES (${DL_INCLUDE_DIRS})
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_DL=YES")
ENDIF()

FIND_PACKAGE( Boost COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


aux_source_directory(src/ SRC_LIST)

add_executable(${PROJECT_NAME} Source.cpp)
add_library(library ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} library stdc++fs ${Boost_LIBRARIES})

 add_executable(UnitTest test/unit_test.cpp)
 target_link_libraries(UnitTest ${GTEST_LIBRARIES} library stdc++fs pthread)

 add_executable(IntegrationTest test/integration_test.cpp)
 target_link_libraries(IntegrationTest ${GTEST_LIBRARIES} library stdc++fs pthread)
