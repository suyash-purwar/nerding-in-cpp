cmake_minimum_required(VERSION 3.25.1)

# A single-line comment

#[==[
A multi-line comment
One more line
]==]

#[[
One more multi-line comment
that spans across multiple lines
]]

message("Hello World")

# Bracket Arguments
# Supports multi-line argument but does not support string interpolation
message([[
    My family members are: [[shubham, sandeep, sangeeta, suyash]]
]])

# Quoted Arguments
# Supports multi-line argument with string interpolation
set(name "suyash")
message("Hey there!
My name is ${name}")

# Unquoted Arguments (hardly used and weird af)
message(one two three) # Here, we are passing three arguments.
message(one/two/three) # Now, it is considered as a single argument.

# Variables
set(age 23)
set("relationship status" single)

message("Suyash's age is ${age}")
message("Suyash is ${relationship\ status}")

set(var1 var2)
set(${var1} "Sorcery") # Value of var1 is var2. So, var2 gets assigned the string Sorcery

message(${var2})

unset(${var1})

#[[
    There are three kind of variables names:
    1) Normal variables (used above)
    2) Environment variables
    3) Cache variables
]]

message("This is from the environment variable my_env: $ENV{my_env}")
set(ENV{my_env} "Update the my_env variable")
message("Updated value for the environment variable my_env: $ENV{my_env}")

#[[
    Notes on ENV variable:
    1) On build configuration, the value of environment variable gets copied into the process memory
    2) Changing the value of environment value does not update the environment variable of the system
]]

# To see it's value, include this file in CMakeLists.txt and then build the project
message("The debug flag is $CACHE{CMAKE_C_FLAGS_DEBUG}")

set(list1 "suyash;shubham;sandeep;sangeeta")
list(LENGTH list1 len_of_list1)
message(len_of_list1)