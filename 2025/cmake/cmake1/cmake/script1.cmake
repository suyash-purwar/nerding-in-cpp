cmake_minimum_required(VERSION 3.25.1)

#[=[
    A comment
]=]

#[[
    Another comment
]]

#[[
    There are three ways to define strings in CMake
    1) Brackets
    2) Quoted
    3) Unquoted
]]

# Brackets: This format respects the tabs and line breaks
message([[
    Multi-line string
    is this?
    YES!
]])

message([==[
    This works too. As long as the number of
    equal operator are matching, it's good.
    Variable interpolation is not supported: ${ CMAKE_VERSION }
]==])

# Quoted: Multi-line string, escaped sequenced, and variable interpolation is supported.
message("Hello, there! \nI am Suyash. \t Tabbed")
message("CMAKE Version = ${CMAKE_VERSION}")
message("I want a job in
systems engineering\n")

# Unquoted: This is some weird shit
message(one\ single\ argument)
message(three separate arguments)
message(three;separate;arguments)
message(Version\ is:\ ${CMAKE_VERSION})