cmake_minimum_required(VERSION 3.25.1)

project(
        ProjectOne
        VERSION 0.1.0
        DESCRIPTION "Project to learn CMake"
        HOMEPAGE_URL "https://cmake.org/"
        LANGUAGES C
)

if ($ENV{PRINT_CONFIG_INFO})
    include("cmake/project_info.cmake")
endif()

if ($ENV{USE_CXX})
    enable_language(CXX)
endif()

add_executable(ProjectOne src/main.c)

#[[
    1. project() → defines the whole project (name, version, metadata) and enables languages in one go.
    2. enable_language() → just enables a specific language’s compiler and settings, usually for conditional
       or incremental language activation.
]]