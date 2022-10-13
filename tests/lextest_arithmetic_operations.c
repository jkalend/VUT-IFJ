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

// prolog
TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)

// $a
TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 2)
TEST_ASSERT(token->column[1] == 3)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

// =
TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 4)
TEST_ASSERT(token->column[1] == 5)

// a
TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 6)
TEST_ASSERT(token->column[1] == 7)
TEST_ASSERT(strcmp(token->value.string, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_PLUS)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 8)
TEST_ASSERT(token->column[1] == 9)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 10)
TEST_ASSERT(token->column[1] == 11)
TEST_ASSERT(strcmp(token->value.number_int, 5) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->column[0] == 11)
TEST_ASSERT(token->column[1] == 12)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "addition_1.php")
