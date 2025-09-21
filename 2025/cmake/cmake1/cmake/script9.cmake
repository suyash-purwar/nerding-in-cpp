#[[
    For making debugging easier, we have a variable CMAKE_MESSAGE_CONTEXT
    that can used to keep track of the branch of execution. It allows for
    better debugging.

    CMAKE_MESSAGE_CONTEXT is a list that works as a stack. As we enter a
    new branch of execution, we append this branch info in the list. When
    the flow execution goes back to the parent scope, the branch info is
    automatically popped from the stack.

    We use a flag `--log-context` to print branch info
]]

list(APPEND CMAKE_MESSAGE_CONTEXT "TOP")
message("In parent scope")

function(print_name name)
    list(APPEND CMAKE_MESSAGE_CONTEXT "PRINT_NAME")
    message(${name})
endfunction()

print_name("Suyash")
print_name("Shubham")

message("Back to parent scope")