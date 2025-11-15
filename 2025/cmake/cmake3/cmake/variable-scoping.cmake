cmake_minimum_required(VERSION 3.25.1)

set(var1 "Hey")

function(Func1)
    set(var1 "Bye") # Creates a variable in the local scope
    message(${var1})
    unset(var1) #  Unsets the local variable's value but global one remains untouched
endfunction()
Func1()

message(${var1})

set(var2 "Sup")

function(Func2)
    set(var2 "What?" PARENT_SCOPE) # Updates the one scope above's variable value
    message(${var2}) # This remains to be "Sup"
endfunction()
Func2()

message(${var2})