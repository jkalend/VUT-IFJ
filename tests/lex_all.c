//
// Created by Kalenda, Jan on 02.10.2022.
//

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

int write_file(const char *filename, const char *content) {
    stream = fopen(filename, "w");
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
    tests_failed += test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment();
    tests_failed += test_only_prologue_with_newline_and_block_comments();
    tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline();
    tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces();
    tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment();
    tests_failed += test_only_prologue_with_multiline_block_comment();
    tests_failed += test_only_prologue_with_declare();
    tests_failed += test_only_prologue_with_comments_and_declare();
    tests_failed += test_only_prologue_with_block_comments_and_declare();
    tests_failed += test_only_prologue_with_more_block_comments_in_declare();
    tests_failed += test_only_prologue_with_multiline_block_comments_in_declare();
    tests_failed += test_only_prologue_with_multiline_block_comments_before_declare();
    tests_failed += test_only_prologue_with_multiline_block_comments_after_declare();
    tests_failed += test_prologue_declare_variable_string();
    tests_failed += test_prologue_declare_variable_int();
    tests_failed += test_prologue_declare_variable_float();
    tests_failed += test_prologue_declare_variable_int_as_string();
    tests_failed += test_prologue_declare_variable_float_as_string();
    tests_failed += test_prologue_declare_variable_float_with_exp();
    tests_failed += test_prologue_declare_variable_float_with_exp_as_string();
	tests_failed += test_var_eq_expression();
	tests_failed += test_type();
    return tests_failed ? 1 : 0;
}
#endif	//LEX_ALL
