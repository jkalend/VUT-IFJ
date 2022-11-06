//
// Created by Jarek Streit on 08.10.2022.
//

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_prologue_declare_variable_string, "Test prologue declare variable string")
    int check = write_file("prologue_declare_variable_string.php",
                           "<?php\ndeclare(strict_types=1);\n$a = \"ahoj\";");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_declare_variable_string.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VAR)
    TEST_ASSERT(token->line == 3)
    TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_ASSIGN)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_STRING)
    TEST_ASSERT(token->line == 3)
    TEST_ASSERT(strcmp(token->value.string, "ahoj") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_declare_variable_string.php")

TEST(test_prologue_declare_variable_int, "Test prologue declare variable int")
    int check = write_file("prologue_declare_variable_int.php",
                           "<?php\ndeclare(strict_types=1);\n$a = 7;");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_declare_variable_int.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VAR)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_ASSIGN)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_INT)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_declare_variable_int.php")

TEST(test_prologue_declare_variable_float, "Test prologue declare variable float")
    int check = write_file("prologue_declare_variable_float.php",
                           "<?php\ndeclare(strict_types=1);\n$a = 2.37;");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_declare_variable_float.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VAR)
    TEST_ASSERT(token->line == 3)
    TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_ASSIGN)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_FLOAT)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_declare_variable_float.php")

TEST(test_prologue_declare_variable_float_as_string, "Test prologue declare variable float as string")
    int check = write_file("prologue_declare_variable_float_as_string.php",
                           "<?php\ndeclare(strict_types=1);\n$a = \"2.37\";");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_declare_variable_float_as_string.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VAR)
    TEST_ASSERT(token->line == 3)
    
    TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_ASSIGN)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_STRING)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(strcmp(token->value.string, "2.37") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_declare_variable_float_as_string.php")

TEST(test_prologue_declare_variable_int_as_string, "Test prologue declare variable int as string")
    int check = write_file("prologue_declare_variable_int_as_string.php",
                           "<?php\ndeclare(strict_types=1);\n$a = \"7\";");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_declare_variable_int_as_string.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VAR)
    TEST_ASSERT(token->line == 3)
    TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_ASSIGN)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_STRING)
    TEST_ASSERT(token->line == 3)
    TEST_ASSERT(strcmp(token->value.string, "7") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_declare_variable_int_as_string.php")

TEST(test_prologue_declare_variable_float_with_exp, "Test prologue declare variable float with exp")
    int check = write_file("prologue_declare_variable_float_with_exp.php",
                           "<?php\ndeclare(strict_types=1);\n$a = 4.2e-7;");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_declare_variable_float_with_exp.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VAR)
    TEST_ASSERT(token->line == 3)
    TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_ASSIGN)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_FLOAT)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_declare_variable_float_with_exp.php")

TEST(test_prologue_declare_variable_float_with_exp_as_string, "Test prologue declare variable float with exp as string")
    int check = write_file("prologue_declare_variable_float_with_exp_as_string.php",
                           "<?php\ndeclare(strict_types=1);\n$a = \"4.2e-7\";");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_declare_variable_float_with_exp_as_string.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VAR)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_ASSIGN)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_STRING)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 3)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_declare_variable_float_with_exp_as_string.php")

TEST(test_var_eq_expression, "Test variable equals expression")
int check = write_file("var_eq_expression.php",
					   "<?php\ndeclare(strict_types=1);\n$a = 5+5;");
if (check != 0) {
	return 1;
}
stream = fopen("var_eq_expression.php", "r");
Token *token = malloc(sizeof(Token));
TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.number_int == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_PLUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.number_int == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "var_eq_expression.php")

#ifndef LEX_ALL
int main(void) {
    int tests_failed = 0;
    tests_failed += test_prologue_declare_variable_string();
    tests_failed += test_prologue_declare_variable_int();
    tests_failed += test_prologue_declare_variable_float();
    tests_failed += test_prologue_declare_variable_int_as_string();
    tests_failed += test_prologue_declare_variable_float_as_string();
    tests_failed += test_prologue_declare_variable_float_with_exp();
    tests_failed += test_prologue_declare_variable_float_with_exp_as_string();
	tests_failed += test_var_eq_expression();
    return tests_failed ? 1 : 0;
}
#endif //LEX_ALL
