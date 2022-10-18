// lextest_arithmetic_operations.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 12.10.2022
// Přeloženo: gcc 9.4.0

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_arithmetic_addition_1, "Test addition 1")
int check = write_file("addition_1.php", "<?php\ndeclare(strict_types=1);\n$a = a + 5;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_PLUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 5) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "addition_1.php")

TEST(test_arithmetic_addition_2, "Test addition 2")
int check = write_file("addition_2.php", "<?php\ndeclare(strict_types=1);\n$a = a + c;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_PLUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "addition_2.php")

TEST(test_arithmetic_addition_3, "Test addition 3")
int check = write_file("addition_3.php", "<?php\ndeclare(strict_types=1);\n$a=a+101;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_PLUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 101) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "addition_3.php")

TEST(test_arithmetic_addition_4, "Test addition 4")
int check = write_file("addition_4.php", "<?php\ndeclare(strict_types=1);\n$a = 1+a    +    19;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(strcmp(token->value.number_int, 1) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_PLUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 4) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_PLUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 19) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "addition_4.php")

TEST(test_arithmetic_subtraction_1, "Test subtraction 1")
int check = write_file("subtraction_1.php", "<?php\ndeclare(strict_types=1);\n$a = a - 5;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MINUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 5) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "subtraction_1.php")

TEST(test_arithmetic_subtraction_2, "Test subtraction 2")
int check = write_file("subtraction_2.php", "<?php\ndeclare(strict_types=1);\n$a = a - c;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MINUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "subtraction_2.php")

TEST(test_arithmetic_subtraction_3, "Test subtraction 3")
int check = write_file("subtraction_3.php", "<?php\ndeclare(strict_types=1);\n$a=a-101;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MINUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 101) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "subtraction_3.php")

TEST(test_arithmetic_subtraction_4, "Test subtraction 4")
int check =
	write_file("subtraction_4.php", "<?php\ndeclare(strict_types=1);\n$a = 1-a    -    19;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(strcmp(token->value.number_int, 1) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MINUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 4) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MINUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 19) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "subtraction_4.php")

TEST(test_arithmetic_multiplication_1, "Test multiplication 1")
int check = write_file("multiplication_1.php", "<?php\ndeclare(strict_types=1);\n$a = a * 5;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MULTIPLY)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 5) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "multiplication_1.php")

TEST(test_arithmetic_multiplication_2, "Test multiplication 2")
int check = write_file("multiplication_2.php", "<?php\ndeclare(strict_types=1);\n$a = a * c;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MULTIPLY)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "multiplication_2.php")

TEST(test_arithmetic_multiplication_3, "Test multiplication 3")
int check = write_file("multiplication_3.php", "<?php\ndeclare(strict_types=1);\n$a=a*101;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MULTIPLY)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 101) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "multiplication_3.php")

TEST(test_arithmetic_multiplication_4, "Test multiplication 4")
int check =
	write_file("multiplication_4.php", "<?php\ndeclare(strict_types=1);\n$a = 1*a    *    19;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(strcmp(token->value.number_int, 1) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MULTIPLY)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 4) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MULTIPLY)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 19) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "multiplication_4.php")

TEST(test_arithmetic_division_1, "Test division 1")
int check = write_file("division_1.php", "<?php\ndeclare(strict_types=1);\n$a = a / 5;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DIVIDE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 5) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "division_1.php")

TEST(test_arithmetic_division_2, "Test division 2")
int check = write_file("division_2.php", "<?php\ndeclare(strict_types=1);\n$a = a / c;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DIVIDE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "division_2.php")

TEST(test_arithmetic_division_3, "Test division 3")
int check = write_file("division_3.php", "<?php\ndeclare(strict_types=1);\n$a=a/101;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DIVIDE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 101) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "division_3.php")

TEST(test_arithmetic_division_4, "Test division 4")
int check = write_file("division_4.php", "<?php\ndeclare(strict_types=1);\n$a = 1/a    /    19;");
if (check != 0) {
	return 1;
}
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
TEST_ASSERT(strcmp(token->value.number_int, 1) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DIVIDE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "A") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DIVIDE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.number_int, 19) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "division_4.php")
