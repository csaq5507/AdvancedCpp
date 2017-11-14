cmake_minimum_required(VERSION 3.5)
project(ex05 LANGUAGES CXX)



if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /wd4141 /WX")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O3 /DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
endif()

aux_source_directory(task1_and_2 SRC_LIST)

add_executable(person_test ${SRC_LIST})
