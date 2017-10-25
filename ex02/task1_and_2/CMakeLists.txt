cmake_minimum_required(VERSION 3.6)

project(VCS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(stdc++fs UNKNOWN IMPORTED)
set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a")

# Link runTests with what we want to test and the GTest and pthread library
aux_source_directory(. SRC_LIST)


add_executable(${PROJECT_NAME} Source.cpp)
add_library(library ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} library stdc++fs)
