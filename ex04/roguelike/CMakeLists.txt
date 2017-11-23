cmake_minimum_required(VERSION 3.5)
project(roguelike LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS})
# -- Compilation

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /wd4141 /WX")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O3 /DNDEBUG")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
endif()

aux_source_directory(src/ SRC_FILES)
aux_source_directory(src/entities SRC_FILES)
aux_source_directory(src/utils SRC_FILES)
aux_source_directory(src/logic SRC_FILES)

add_executable(roguelike ${SRC_FILES})

# Scan through resource folder for updated files and copy if none existing or
file (GLOB_RECURSE resources "resources/*.*")
foreach(resource ${resources})
    get_filename_component(filename ${resource} NAME)
    get_filename_component(dir ${resource} DIRECTORY)
    get_filename_component(dirname ${dir} NAME)

    set (output "")

    while(NOT ${dirname} STREQUAL resources)
        get_filename_component(path_component ${dir} NAME)
        set (output "${path_component}/${output}")
        get_filename_component(dir ${dir} DIRECTORY)
        get_filename_component(dirname ${dir} NAME)
    endwhile()

    set(output "${CMAKE_CURRENT_BINARY_DIR}/resources/${output}/${filename}")

    add_custom_command(
            COMMENT "Moving updated resource-file '${filename}'"
            OUTPUT ${output}
            DEPENDS ${resource}
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${resource}
            ${output}
    )
    add_custom_target(${filename} ALL DEPENDS ${resource} ${output})

endforeach()

target_include_directories(roguelike PUBLIC include)

target_include_directories(roguelike SYSTEM PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

target_link_libraries(roguelike
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2TTF_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
)
