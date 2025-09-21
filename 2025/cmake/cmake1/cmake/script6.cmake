cmake_minimum_required(VERSION 3.25.1)

#[[
    There are two kinds of loops
    -> While loop
    -> Foreach loop
        - Ranged based
        - List based
        - List based with Zip List
]]

set(counter 1)

while(counter LESS_EQUAL 10)
    message(${counter})
    math(EXPR counter "${counter} + 1")
endwhile()

# Range here is from 0 to 3, all inclusive
foreach (c1 RANGE 3)
    message(${c1})
endforeach()

# Range from 100 to 130 with a step of 5
foreach (c2 RANGE 100 130 5)
    message(${c2})
endforeach()

set(list1 suyash shubham sandeep sangeeta)
foreach (name IN LISTS list1)
    message(${name})
endforeach()

# The shorthand version
# vegeatable is the variable, and rest are items of the list
foreach (vegetable tomato cucumber potato onion)
    message(${vegetable})
endforeach()

set(names suyash shubham sandeep sangeeta)
set(ages 22 27 58 55)

foreach (name age IN ZIP_LISTS names ages)
    message("${name}'s age is ${age}")
endforeach()