cmake_minimum_required(VERSION 3.16)
project(IFJ C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals" ${CMAKE_MODULE_PATH})
find_package(codecov)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-arcs -ftest-coverage -O2 -pedantic -Wall -Wextra")

include_directories(.)
include_directories(src)
include_directories(tests)

set(PARSER src/parser.c src/parser.h src/error.h src/symtable.h src/symtable.c src/stack.c src/stack.h)
set(SCANNER src/scanner.c src/scanner.h src/error.h)

set(LEX_ALL tests/lextest_empty.c tests/lex_all.c tests/lex_all.h tests/lextest_only_prologue.c
        tests/lextest_variables_operations.c tests/lextest_arithmetic_operations.c tests/lextest_cycles.c
        tests/lextest_functions.c tests/lextest_if_statements.c tests/lextest_relation_operators.c
        tests/lextest_error.c)
set(GEN src/generator.c src/generator.h src/error.h src/symtable.h src/symtable.c)

add_executable(IFJ ${PARSER} ${SCANNER} ${GEN})
add_coverage(IFJ)
target_link_libraries(IFJ m)

#add_executable(parser
#        ${PARSER} ${SCANNER})
#add_coverage(parser)
#
#add_executable(test_stack
#        tests/stack_test.c src/stack.h src/stack.c)
#add_coverage(test_stack)
#
#add_executable(all_tests_lexer
#        ${LEX_ALL} ${SCANNER})
#add_coverage(all_tests_lexer)
#target_compile_options(all_tests_lexer PRIVATE -DLEX_ALL)
#
#add_executable(lex_empty
#        tests/lextest_empty.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_empty)
#
#add_executable(lex_only_prologue
#        tests/lextest_only_prologue.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_only_prologue)
#
#add_executable(lex_extreme_prologue
#        tests/lextest_prologue_extreme.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_extreme_prologue)
#
#add_executable(lex_variables_operations
#        tests/lextest_variables_operations.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_variables_operations)
#
#add_executable(lex_arithmetic_operations
#        tests/lextest_arithmetic_operations.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_arithmetic_operations)
#
#add_executable(lex_cycles
#        tests/lextest_cycles.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_cycles)
#
#add_executable(lex_functions
#        tests/lextest_functions.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_functions)
#
#add_executable(lex_if_statements
#        tests/lextest_if_statements.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_if_statements)
#
#add_executable(lex_relation_operators
#        tests/lextest_relation_operators.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_relation_operators)
#
#add_executable(lex_errors
#        tests/lextest_error.c tests/lex_all.c tests/lex_all.h ${SCANNER})
#add_coverage(lex_errors)
#
#enable_testing()
#
#add_test(NAME stack_test COMMAND $<TARGET_FILE:test_stack>)
#add_test(NAME all_tests_lexer COMMAND $<TARGET_FILE:all_tests_lexer>)
#add_test(NAME lexer_test_empty COMMAND $<TARGET_FILE:lex_empty>)
#add_test(NAME lexer_test_only_prologue COMMAND $<TARGET_FILE:lex_only_prologue>)
#add_test(NAME lexer_test_extreme_prologue COMMAND $<TARGET_FILE:lex_extreme_prologue>)
#add_test(NAME lexer_test_variables_operations COMMAND $<TARGET_FILE:lex_variables_operations>)
#add_test(NAME lexer_test_arithmetic_operations COMMAND $<TARGET_FILE:lex_arithmetic_operations>)
#add_test(NAME lexer_test_cycles COMMAND $<TARGET_FILE:lex_cycles>)
#add_test(NAME lexer_test_functions COMMAND $<TARGET_FILE:lex_functions>)
#add_test(NAME lexer_test_if_statements COMMAND $<TARGET_FILE:lex_if_statements>)
#add_test(NAME lexer_test_relation_operators COMMAND $<TARGET_FILE:lex_relation_operators>)
#add_test(NAME lexer_test_errors COMMAND $<TARGET_FILE:lex_errors>)