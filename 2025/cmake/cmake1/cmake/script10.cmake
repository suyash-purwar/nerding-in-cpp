cmake_minimum_required(VERSION 3.25.1)

include_guard(GLOBAL)

set(list1 suyash sandeep sangam sourav)

foreach(list1_item IN LISTS list1 satyam)
    message(${list1_item})
endforeach ()

message("${CMAKE_MODULE_PATH}")