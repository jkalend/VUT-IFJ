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
Token *token = malloc(sizeof(Token));
for (int i = 0; i < 8; i++) {
	if (get_token(token)) {
		return 1;
	}
}

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 7)
TEST_ASSERT(token->column[1] == 11)
TEST_ASSERT(strcmp(token->value.string, "ahoj") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 12)
TEST_ASSERT(token->column[1] == 13)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "prologue_declare_variable_string.php")

TEST(test_prologue_declare_variable_int, "Test prologue declare variable int")
int check =
	write_file("prologue_declare_variable_int.php", "<?php\ndeclare(strict_types=1);\n$a = 7;");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));
for (int i = 0; i < 8; i++) {
	if (get_token(token)) {
		return 1;
	}
}

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 6)
TEST_ASSERT(token->column[1] == 7)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 7)
TEST_ASSERT(token->column[1] == 8)

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
Token *token = malloc(sizeof(Token));
for (int i = 0; i < 8; i++) {
	if (get_token(token)) {
		return 1;
	}
}

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_FLOAT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 6)
TEST_ASSERT(token->column[1] == 10)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 10)
TEST_ASSERT(token->column[1] == 11)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "prologue_declare_variable_float.php")

TEST(test_prologue_declare_variable_float_as_string,
	 "Test prologue declare variable float as string")
int check = write_file("prologue_declare_variable_float_as_string.php",
					   "<?php\ndeclare(strict_types=1);\n$a = \"2.37\";");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));
for (int i = 0; i < 8; i++) {
	if (get_token(token)) {
		return 1;
	}
}

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 7)
TEST_ASSERT(token->column[1] == 11)
TEST_ASSERT(strcmp(token->value.string, "2.37") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 12)
TEST_ASSERT(token->column[1] == 13)

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
Token *token = malloc(sizeof(Token));
for (int i = 0; i < 8; i++) {
	if (get_token(token)) {
		return 1;
	}
}

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 7)
TEST_ASSERT(token->column[1] == 8)
TEST_ASSERT(strcmp(token->value.string, "7") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 9)
TEST_ASSERT(token->column[1] == 10)

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
Token *token = malloc(sizeof(Token));
for (int i = 0; i < 8; i++) {
	if (get_token(token)) {
		return 1;
	}
}

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_FLOAT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 6)
TEST_ASSERT(token->column[1] == 12)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 12)
TEST_ASSERT(token->column[1] == 13)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "prologue_declare_variable_float_with_exp.php")

TEST(test_prologue_declare_variable_float_with_exp_as_string,
	 "Test prologue declare variable float with exp as string")
int check = write_file("prologue_declare_variable_float_with_exp_as_string.php",
					   "<?php\ndeclare(strict_types=1);\n$a = \"4.2e-7\";");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));
for (int i = 0; i < 8; i++) {
	if (get_token(token)) {
		return 1;
	}
}

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_FLOAT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 7)
TEST_ASSERT(token->column[1] == 13)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 14)
TEST_ASSERT(token->column[1] == 15)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "prologue_declare_variable_float_with_exp_as_string.php")

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
	return tests_failed ? 1 : 0;
}
#endif	//LEX_ALL
