cmake_minimum_required(VERSION 3.16)
project(IFJ C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -g -O0 -pedantic -Wall -Wextra")

include_directories(.)
include_directories(src)
include_directories(tests)

add_executable(test_stack
        tests/stack_test.c src/stack.h src/stack.c tests/stack_test.c)

enable_testing()

add_test(NAME stack_test COMMAND $<TARGET_FILE:test_stack>)