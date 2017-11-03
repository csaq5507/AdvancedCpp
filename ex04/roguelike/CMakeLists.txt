cmake_minimum_required(VERSION 3.5)
project(roguelike LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include(defaults)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# -- Compilation

add_executable(roguelike
    src/entities/player.cc
    src/entity.cc
    src/game.cc
    src/main.cc
    src/resource_loader.cc
    src/sprite_set.cc
    src/utils/vec2.cc
)

target_include_directories(roguelike PUBLIC include)

target_include_directories(roguelike SYSTEM PUBLIC
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

target_link_libraries(roguelike
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)
