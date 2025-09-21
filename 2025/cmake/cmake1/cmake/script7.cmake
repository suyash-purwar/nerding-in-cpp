cmake_minimum_required(VERSION 3.25.1)

function(func1 arg1 arg2)
    message("Current function: ${CMAKE_CURRENT_FUNCTION}")
    message("File: ${CMAKE_CURRENT_FUNCTION_LIST_FILE}")
    message("Directory: ${CMAKE_CURRENT_FUNCTION_LIST_DIR}")
    message("Line: ${CMAKE_CURRENT_FUNCTION_LIST_LINE}")
    message("First arg: ${arg1}")
    message("Arg count: ${ARGC}")
    message("Arg0: ${ARGV0}")
    message("Arg1: ${ARGV1}")
endfunction()

func1(100 120)

function(B)
    message("B")
endfunction()

function(A)
    message("A")
    B()
endfunction()

A()
