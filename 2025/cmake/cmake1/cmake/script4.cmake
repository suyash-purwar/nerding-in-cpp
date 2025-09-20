cmake_minimum_required(VERSION 3.25.1)

# Ways to create list

set(list1 "a;b;c;d;e")
set(list2 1 2 3 4 5)
set(list3 a b "4;5;6")

message(${list1})
message(${list1}\ ${list2}\ ${list3})

list(LENGTH list1 list1_length)
message(${list1_length})

list(GET list2 2 list2_at_index_2)
message(${list2_at_index_2})

list(REVERSE list3)
message(${list3})

#[[
    Short Summary of other list functions

    list(LENGTH <list> <out-var>)
    list(GET <list> <element index> [<index> ...] <out-var>)
    list(JOIN <list> <glue> <out-var>)
    list(SUBLIST <list> <begin> <length> <out-var>)
    list(FIND <list> <value> <out-var>)
    list(APPEND <list> [<element>...])
    list(FILTER <list> {INCLUDE | EXCLUDE} REGEX <regex>)
    list(INSERT <list> <index> [<element>...])
    list(POP_BACK <list> [<out-var>...])
    list(POP_FRONT <list> [<out-var>...])
    list(PREPEND <list> [<element>...])
    list(REMOVE_ITEM <list> <value>...)
    list(REMOVE_AT <list> <index>...)
    list(REMOVE_DUPLICATES <list>)
    list(TRANSFORM <list> <ACTION> [...])
    list(REVERSE <list>)
    list(SORT <list> [...])
]]