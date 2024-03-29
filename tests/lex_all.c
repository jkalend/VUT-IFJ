//
// Created by Kalenda, Jan on 02.10.2022.
//

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

int write_file(const char *filename, const char *content) {
	FILE *stream = fopen(filename, "w");
	if (stream == NULL) {
		return 1;
	}
	fprintf(stream, "%s", content);
	fclose(stream);
	return 0;
}

#ifdef LEX_ALL
int main(void) {
	int tests_failed = 0;
	tests_failed += test_empty();
	tests_failed += test_only_prologue();
	tests_failed += test_only_prologue_with_spaces();
	tests_failed += test_only_prologue_with_newline();
	tests_failed += test_only_prologue_with_newline_and_spaces();
	tests_failed += test_only_prologue_with_newline_and_spaces_and_comment();
	tests_failed += test_only_prologue_with_newline_and_spaces_and_comment_and_newline();
	tests_failed += test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces();
	tests_failed +=
		test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment();
	tests_failed += test_only_prologue_with_newline_and_block_comments();
	tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline();
	tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces();
	tests_failed +=
		test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment();
	tests_failed += test_only_prologue_with_multiline_block_comment();
	tests_failed += test_only_prologue_with_declare();
	tests_failed += test_prologue_declare_variable_string();
	tests_failed += test_prologue_declare_variable_int();
	tests_failed += test_prologue_declare_variable_float();
	tests_failed += test_prologue_declare_variable_int_as_string();
	tests_failed += test_prologue_declare_variable_float_as_string();
	tests_failed += test_prologue_declare_variable_float_with_exp();
	tests_failed += test_prologue_declare_variable_float_with_exp_as_string();
	tests_failed += test_arithmetic_addition_1();
	tests_failed += test_arithmetic_addition_2();
	tests_failed += test_arithmetic_addition_3();
	tests_failed += test_arithmetic_addition_4();
	tests_failed += test_arithmetic_subtraction_1();
	tests_failed += test_arithmetic_subtraction_2();
	tests_failed += test_arithmetic_subtraction_3();
	tests_failed += test_arithmetic_subtraction_4();
	tests_failed += test_arithmetic_multiplication_1();
	tests_failed += test_arithmetic_multiplication_2();
	tests_failed += test_arithmetic_multiplication_3();
	tests_failed += test_arithmetic_multiplication_4();
	tests_failed += test_arithmetic_division_1();
	tests_failed += test_arithmetic_division_2();
	tests_failed += test_arithmetic_division_3();
	tests_failed += test_arithmetic_division_4();
	tests_failed += test_if_statement_1();
	tests_failed += test_if_statement_2();
	tests_failed += test_if_statement_3();
	tests_failed += test_if_statement_4();
	tests_failed += test_if_else_statement_1();
	tests_failed += test_if_else_statement_2();
	tests_failed += test_if_statement_else_3();
	tests_failed += test_if_else_statement_4();
	tests_failed += test_while_1();
	tests_failed += test_while_2();
	tests_failed += test_while_3();
	tests_failed += test_func_definition_1();
	tests_failed += test_func_definition_2();
	tests_failed += test_func_definition_3();
	tests_failed += test_func_call_1();
	tests_failed += test_greater_1();
	tests_failed += test_greater_2();
	tests_failed += test_greater_3();
	tests_failed += test_lesser_1();
	tests_failed += test_lesser_2();
	tests_failed += test_lesser_3();
	tests_failed += test_greater_equal_1();
	tests_failed += test_greater_equal_2();
	tests_failed += test_greater_equal_3();
	tests_failed += test_lesser_equal_1();
	tests_failed += test_lesser_equal_2();
	tests_failed += test_lesser_equal_3();
	tests_failed += test_equal_1();
	tests_failed += test_equal_2();
	tests_failed += test_equal_3();
	tests_failed += test_not_equal_1();
	tests_failed += test_not_equal_2();
	tests_failed += test_not_equal_3();
	tests_failed += test_faulty_declare();
	tests_failed += test_faulty_type();
	tests_failed += test_faulty_number();
	tests_failed += test_faulty_characters_and_combinations();
	//tests_failed += test_faulty_identifier();
	//tests_failed += test_faulty_variable();
	return tests_failed ? 1 : 0;
}
#endif	//LEX_ALL
