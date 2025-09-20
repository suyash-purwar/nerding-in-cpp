cmake_minimum_required(VERSION 3.25.1)

#[[
    There are three kind of variables in CMake
    -> Normal script variables
    -> Environment variables: These variables are picked from the system when scripts runs
    -> Cache variables: These variables are from CMakeCache.txt
]]

# Normal variables
set(var1 "val1")
message(var1)

set([[var 2]] [[
Hold my multi-line string
    - Suyash]])
message(${var\ 2})

set(cmake_ver ${CMAKE_VERSION})
message(${cmake_ver})
unset(cmaker_ver)
message(${cmake_ver})

#[[
 - The `${inner}` variable is evaluated first and it evaluates to "Inner"
 - After expansion, the outer expression becomes `${outerInner}`
 - `${outerInner}` expands to "Outer"
]]
set(inner "Inner")
set(outerInner "Outer")
message(${outer${inner}}) #

#[[
 - Here, we are not altering the value of CMAKE_VERSION variable
 - ${CMAKE_VERSION} expands to my current cmake version (4.1.1)
 - We are creating a variable named as 4.1.1 with a value of "0_0_0"
]]
set(${CMAKE_VERSION} "0_0_0")
message(${CMAKE_VERSION})
message(${4.1.1})

#[[
    -> Environment variables are picked up from the shell environment variables
    -> The value of these environment variables can be changed from the script
       but it stays that way for the current process or the child processes
    -> It doesn't persist between cmake runs
]]

message($ENV{SOMETHING}) # Prints "Hi" when run like this "SOMETHING=Hi cmake -P <file_name>"

set(ENV{SOMETHING} "HELLO") # Overrides the value with "HELLO"
message($ENV{SOMETHING})

#[[
    -> Cache variables are picked up from CMakeCache.txt file present in the build directory
    -> CMAKE_COLOR_MAKEFILE is defined in the cache file. When we run the script by including
       this script in the CMakeLists.txt file, the value gets printed.
    -> When this script file runs independently, it wouldn't compile as it is not aware of the
       cache file.
]]
message($CACHE{CMAKE_COLOR_MAKEFILE})

set(OWNER_NAME "suyash" CACHE STRING "Name of the person")
message($CACHE{OWNER_NAME})