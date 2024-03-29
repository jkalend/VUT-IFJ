// lextest_if_statements.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 16.10.2022
// Přeloženo: gcc 9.4.0

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_if_statement_1, "Test if statement 1")
	int check = write_file("if_1.php", "<?php declare(strict_types=1);\nif($temp === null){}");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_1.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "temp") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EQUAL)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_NULL)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_1.php")

TEST(test_if_statement_2, "Test if statement 2")
	int check = write_file("if_2.php", "<?php declare(strict_types=1);\nif($temp >= 8){\n}");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_2.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "temp") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_GREATER_EQUAL)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_INT)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.number_int == 8)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_2.php")

TEST(test_if_statement_3, "Test if statement 3")
	int check =
			write_file("if_3.php",
			           "<?php declare(strict_types=1);\nif($temp === null){\n$var = \"Hello World!\";\n}");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_3.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "temp") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EQUAL)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_NULL)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 3)
	TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_ASSIGN)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_STRING)
	TEST_ASSERT(token->line == 3)
	TEST_ASSERT(strcmp(token->value.string, "Hello World!") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_SEMICOLON)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_3.php")

TEST(test_if_statement_4, "Test if statement 4")
	int check = write_file("if_4.php", "<?php declare(strict_types=1);\nif(1){$var = $c;}");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_4.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_INT)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.number_int == 1)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_ASSIGN)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_SEMICOLON)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_4.php")

//-------------------------------------------
//-------------------------------------------
//-------------------------------------------

TEST(test_if_else_statement_1, "Test if else statement 1")
	int check =
			write_file("if_else_1.php", "<?php declare(strict_types=1);\nif($temp === null){}\nelse { }");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_else_1.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "temp") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EQUAL)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_NULL)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 3)
	TEST_ASSERT(token->value.keyword == KW_ELSE)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_else_1.php")

TEST(test_if_else_statement_2, "Test if else statement 2")
	int check = write_file("if_else_2.php",
	                       "<?php declare(strict_types=1);\nif($temp <= 8){\n}\nelse { $a_h = $a+$B; }");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_else_2.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "temp") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LESS_EQUAL)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_INT)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.number_int == 8)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 4)
	TEST_ASSERT(token->value.keyword == KW_ELSE)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 4)
	TEST_ASSERT(strcmp(token->value.identifier, "a_h") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_ASSIGN)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 4)
	TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_PLUS)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 4)
	TEST_ASSERT(strcmp(token->value.identifier, "B") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_SEMICOLON)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_else_2.php")

TEST(test_if_statement_else_3, "Test if else statement 3")
	int check = write_file(
			"if_else_3.php",
			"<?php declare(strict_types=1);\nif($temp !== null){\n$var = \"Hello World!\";\n}\nelse {$var = \"I hate the world!\";}");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_else_3.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.string, "temp") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_NOT_EQUAL)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_NULL)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 3)
	TEST_ASSERT(strcmp(token->value.string, "var") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_ASSIGN)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_STRING)
	TEST_ASSERT(token->line == 3)
	TEST_ASSERT(strcmp(token->value.string, "Hello World!") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_SEMICOLON)
	TEST_ASSERT(token->line == 3)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 5)
	TEST_ASSERT(token->value.keyword == KW_ELSE)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 5)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 5)
	TEST_ASSERT(strcmp(token->value.string, "var") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_ASSIGN)
	TEST_ASSERT(token->line == 5)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_STRING)
	TEST_ASSERT(token->line == 5)
	TEST_ASSERT(strcmp(token->value.string, "I hate the world!") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_SEMICOLON)
	TEST_ASSERT(token->line == 5)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 5)
	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_else_3.php")

TEST(test_if_else_statement_4, "Test if else statement 4")
	int check = write_file(
			"if_else_4.php", "<?php declare(strict_types=1);\nif(1){$var = $c}\nelse \n{\n$brrrr = 42; }");
	if (check != 0) {
		return 1;
	}
	scanner.stream = fopen("if_else_4.php", "r");
	Token *token = malloc(sizeof(Token));

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VALID)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.keyword == KW_IF)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_INT)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(token->value.number_int == 1)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACKET)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_ASSIGN)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 2)
	TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 2)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_KEYWORD)
	TEST_ASSERT(token->line == 3)
	TEST_ASSERT(token->value.keyword == KW_ELSE)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_LEFT_BRACE)
	TEST_ASSERT(token->line == 4)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_VAR)
	TEST_ASSERT(token->line == 5)
	TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_ASSIGN)
	TEST_ASSERT(token->line == 5)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_INT)
	TEST_ASSERT(token->line == 5)
	TEST_ASSERT(token->value.number_int == 42)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_SEMICOLON)
	TEST_ASSERT(token->line == 5)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_RIGHT_BRACE)
	TEST_ASSERT(token->line == 5)

	TEST_ASSERT(get_token(token, &scanner) == 0)
	TEST_ASSERT(token->type == T_EOF)

	free(token);
ENDTEST(scanner.stream, "if_else_4.php")

#ifndef LEX_ALL
int main(void)
{
	int tests_failed = 0;
	tests_failed += test_if_statement_1();
	tests_failed += test_if_statement_2();
	tests_failed += test_if_statement_3();
	tests_failed += test_if_statement_4();
	tests_failed += test_if_else_statement_1();
	tests_failed += test_if_else_statement_2();
	tests_failed += test_if_statement_else_3();
	tests_failed += test_if_else_statement_4();
	return tests_failed ? 1 : 0;
}
#endif // LEX_ALL
