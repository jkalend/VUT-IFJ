//
// Created by Kalenda, Jan on 02.10.2022.
//

#ifndef IFJ_LEX_ALL_H
#define IFJ_LEX_ALL_H

#include <string.h>
#include "scanner.h"
#include "stack.h"


static Scanner scanner;

#define TEST(NAME, DESCRIPTION)                                                \
int NAME() {                                                                   \
    int STATUS = 0;                                                            \
    scanner.line = 1;                                                                  \
    scanner.first_read = 0;                                                            \
    printf("\n[%s] %s\n\n", #NAME, DESCRIPTION);                               \

#define TEST_ASSERT(CONDITION)                                                 \
    if (CONDITION) {                                                           \
        PASS("Assertion suceeded: " #CONDITION);                               \
    } else {                                                                   \
        FAIL("Assertion failed: " #CONDITION);                                 \
        STATUS = 1;                                                            \
    }

#define ENDTEST(STREAM, FILE)                                                  \
    fclose(STREAM);                                                            \
    remove(FILE);                                                              \
    printf("\n");                                                              \
    return STATUS;                                                             \
}

#define FAIL(REASON) printf("[FAILED] %s\n", REASON)

#define PASS(REASON) printf("[PASSED] %s\n", REASON)

int write_file(const char *filename, const char *content);

int test_empty(void);

int test_only_prologue(void);

int test_only_prologue_with_spaces(void);

int test_only_prologue_with_newline(void);

int test_only_prologue_with_newline_and_spaces(void);

int test_only_prologue_with_newline_and_spaces_and_comment(void);

int test_only_prologue_with_newline_and_spaces_and_comment_and_newline(void);

int test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces(void);

int test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment(void);

int test_only_prologue_with_newline_and_block_comments(void);

int test_only_prologue_with_newline_and_block_comments_and_newline(void);

int test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces(void);

int test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment(void);

int test_only_prologue_with_multiline_block_comment(void);

int test_only_prologue_with_declare(void);

int test_only_prologue_with_comments_and_declare(void);

int test_only_prologue_with_block_comments_and_declare(void);

int test_only_prologue_with_more_block_comments_in_declare(void);

int test_only_prologue_with_multiline_block_comments_in_declare(void);

int test_only_prologue_with_multiline_block_comments_before_declare(void);

int test_only_prologue_with_multiline_block_comments_after_declare(void);

int test_prologue_declare_variable_string(void);

int test_prologue_declare_variable_int(void);

int test_prologue_declare_variable_float(void);

int test_prologue_declare_variable_int_as_string(void);

int test_prologue_declare_variable_float_as_string(void);

int test_prologue_declare_variable_float_with_exp(void);

int test_prologue_declare_variable_float_with_exp_as_string(void);

int test_arithmetic_addition_1(void);

int test_arithmetic_addition_2(void);

int test_arithmetic_addition_3(void);

int test_arithmetic_addition_4(void);

int test_arithmetic_subtraction_1(void);

int test_arithmetic_subtraction_2(void);

int test_arithmetic_subtraction_3(void);

int test_arithmetic_subtraction_4(void);

int test_arithmetic_multiplication_1(void);

int test_arithmetic_multiplication_2(void);

int test_arithmetic_multiplication_3(void);

int test_arithmetic_multiplication_4(void);

int test_arithmetic_division_1(void);

int test_arithmetic_division_2(void);

int test_arithmetic_division_3(void);

int test_arithmetic_division_4(void);

int test_if_statement_1(void);

int test_if_statement_2(void);

int test_if_statement_3(void);

int test_if_statement_4(void);

int test_if_else_statement_1(void);

int test_if_else_statement_2(void);

int test_if_statement_else_3(void);

int test_if_else_statement_4(void);

int test_while_1(void);

int test_while_2(void);

int test_while_3(void);

int test_func_definition_1(void);

int test_func_definition_2(void);

int test_func_definition_3(void);

int test_func_call_1(void);

int test_greater_1(void);

int test_greater_2(void);

int test_greater_3(void);

int test_lesser_1(void);

int test_lesser_2(void);

int test_lesser_3(void);

int test_greater_equal_1(void);

int test_greater_equal_2(void);

int test_greater_equal_3(void);

int test_lesser_equal_1(void);

int test_lesser_equal_2(void);

int test_lesser_equal_3(void);

int test_equal_1(void);

int test_equal_2(void);

int test_equal_3(void);

int test_not_equal_1(void);

int test_not_equal_2(void);

int test_not_equal_3(void);

int test_faulty_declare(void);

//int test_faulty_identifier(void);

//int test_faulty_variable(void);

int test_faulty_type(void);

int test_faulty_number(void);

int test_faulty_characters_and_combinations(void);

#endif	//IFJ_LEX_ALL_H
