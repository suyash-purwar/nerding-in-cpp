cmake_minimum_required(VERSION 3.25.1)

function(print_project_info)
    message("Project name: ${PROJECT_NAME}")
    message("Project version: ${PROJECT_VERSION}")
    message("Project description: ${PROJECT_DESCRIPTION}")
    message("Project homepage URL: ${PROJECT_HOMEPAGE_URL}")

    message("Project source dir: ${PROJECT_SOURCE_DIR}")
    message("Project binary dir: ${PROJECT_BINARY_DIR}")

    message("C Compiler: ${CMAKE_C_COMPILER}")
    message("C Standard: ${CMAKE_C_STANDARD}")
endfunction()

print_project_info()