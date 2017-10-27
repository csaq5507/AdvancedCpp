cmake_minimum_required(VERSION 3.6)
project(AdvancedCpp LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/ex02/module)

add_subdirectory(
        ex03/
)

