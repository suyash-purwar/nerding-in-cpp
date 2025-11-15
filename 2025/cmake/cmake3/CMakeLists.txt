cmake_minimum_required(VERSION 3.25.1)

project(Hello)

include(cmake/script.cmake)
add_executable(Hello src/main.c)
