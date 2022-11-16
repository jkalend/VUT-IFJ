// lextest_cycles.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 18.10.2022
// Přeloženo: gcc 9.4.0

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_while_1, "Test while cycle 1")
int check = write_file("while_1.php", "<?phwp declare(strict_types=1);\nwhile(true)\n{}");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.keyword, KW_WHILE) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "while_1.php")

TEST(test_while_2, "Test while cycle 2")
int check = write_file("while_2.php",
					   "<?phwp declare(strict_types=1);\nwhile($a)\n{ if($b)\n{$a = false;}}");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.keyword, KW_WHILE) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.keyword, KW_IF) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "b") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.keyword, KW_FALSE) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "while_2.php")

TEST(test_while_3, "Test while cycle 3")
int check = write_file("while_3.php",
					   "<?phwp declare(strict_types=1);\nwhile($vruuum > 0)\n{$emil = $emil - 2;}");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.keyword, KW_WHILE) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "vruuum") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_GREATER)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.number_int, 0) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "emil") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "emil") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_MINUS)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.number_int, 2) == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "while_3.php")

#ifndef LEX_ALL
int main(void)
{
    int tests_failed = 0;
    tests_failed += test_while_1();
    tests_failed += test_while_2();
    tests_failed += test_while_3();
    return tests_failed ? 1 : 0;
}
#endif // LEX_ALL
