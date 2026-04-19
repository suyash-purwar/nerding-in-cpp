cmake_minimum_required(VERSION 3.28)
project(nerding-in-cpp C)

set(CMAKE_C_STANDARD 11)

# 1. Collect files (GLOB is okay for small learning projects, but list explicitly for real ones)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.c")

# 2. Print the actual list of files for debugging
message(STATUS "Source files found: ${SRC_FILES}")

foreach(file ${SRC_FILES})
    # Get relative path to avoid absolute paths in target names
    file(RELATIVE_PATH rel_file ${CMAKE_CURRENT_SOURCE_DIR} ${file})

    # Replace slashes with underscores (e.g., src1/main.c -> src1_main)
    string(REPLACE "/" "_" target_name ${rel_file})
    string(REPLACE ".c" "" target_name ${target_name})

    add_executable(${target_name} ${file})
endforeach()