cmake_minimum_required(VERSION 3.25.1)

set(EMPTY_STRING "\"\"")

set(var_true TRUE)
set(var_false FALSE)
set(var_on ON)
set(var_off OFF)
set(var_yes YES)
set(var_no NO)
set(var_zero 0)
set(var_one 1)
set(var_empty_string "")
set(var_string "HEY")

set(TRUTHY_VALUES ${var_true} ${var_on} ${var_yes} ${var_one} ${var_string})
set(FALSY_VALUES ${var_false} ${var_off} ${var_no} ${var_zero} ${var_empty_string})

list(JOIN TRUTHY_VALUES ", " PRESENTABLE_T_VALUE_LIST)
list(JOIN FALSY_VALUES ", " PRESENTABLE_F_VALUE_LIST)

if (var_true AND var_on AND var_yes AND var_one AND var_string)
    message("Truthy values: ${PRESENTABLE_T_VALUE_LIST}")
endif()

if (NOT(var_false AND var_off AND var_no AND var_zero AND var_empty_string))
    message("Falsy values: ${PRESENTABLE_F_VALUE_LIST}, ${EMPTY_STRING}")
endif()
