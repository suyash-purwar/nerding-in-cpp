cmake_minimum_required(VERSION 3.25.1)

# Variable scoping

function(Outer)
    message("Outer ${A}")
    set(A 2 PARENT_SCOPE)
    Inner()
    message("Outer ${A}")
endfunction()

function(Inner)
    message("Inner ${A}")
    set(A 3)
    message("Inner ${A}")
endfunction()

set(A 1)
message("Global ${A}")
Outer()
message("Global ${A}")