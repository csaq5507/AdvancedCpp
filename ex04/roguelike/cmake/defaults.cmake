# Build Type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "CMake Build Type" FORCE)
endif()

# Link Dynamically
if(NOT DEFINED BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build Shared Libraries" FORCE)
endif()

# CXX Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings
set(_ids GNU CLang AppleClang)
if(CMAKE_CXX_COMPILER_ID IN_LIST _ids)
    add_compile_options(-Wall -Wextra)
endif()
unset(_ids)
