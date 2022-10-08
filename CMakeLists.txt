cmake_minimum_required(VERSION 3.16)
project(IFJ C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals" ${CMAKE_MODULE_PATH})
find_package(codecov)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -g -O0 -pedantic -Wall -Wextra")

include_directories(.)
include_directories(src)
include_directories(tests)

set(SCANNER src/scanner.c src/scanner.h src/error.h)
set(LEX_ALL tests/lextest_empty.c tests/lex_all.c tests/lex_all.h tests/lextest_only_prologue.c)

add_executable(test_stack
        tests/stack_test.c src/stack.h src/stack.c)
add_coverage(test_stack)

add_executable(all_tests_lexer
        ${LEX_ALL} ${SCANNER})
add_coverage(all_tests_lexer)
target_compile_options(all_tests_lexer PRIVATE -DLEX_ALL)

add_executable(lex_empty
        tests/lextest_empty.c tests/lex_all.c tests/lex_all.h ${SCANNER})
add_coverage(lex_empty)

add_executable(lex_only_prologue
        tests/lextest_only_prologue.c tests/lex_all.c tests/lex_all.h ${SCANNER})

enable_testing()

add_test(NAME stack_test COMMAND $<TARGET_FILE:test_stack>)
add_test(NAME all_tests_lexer COMMAND $<TARGET_FILE:all_tests_lexer>)
add_test(NAME lexer_test_empty COMMAND $<TARGET_FILE:lex_empty>)
add_test(NAME lexer_test_only_prologue COMMAND $<TARGET_FILE:lex_only_prologue>)
