project(Task4)

cmake_minimum_required(VERSION 2.8)
 
ADD_DEFINITIONS(
    -std=c++14
    -Wall
    -Wextra
)
 

 
# Link runTests with what we want to test and the GTest and pthread library
aux_source_directory(. SRC_LIST)
aux_source_directory(app/ SRC_LIST)
aux_source_directory(libBar/ SRC_LIST)
aux_source_directory(libBaz/ SRC_LIST)
aux_source_directory(libFoo/ SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
