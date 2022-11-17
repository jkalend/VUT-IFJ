// lextest_relation_operators.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 07.11.2022
// Přeloženo: gcc 9.4.0

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_greater_1, "Test greater 1")
int check = write_file("greater_1.php", "if(1 > c)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
stream = fopen("greater_1.php", "r");
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_GREATER)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "greater_1.php")

TEST(test_greater_2, "Test greater 2")
int check = write_file("greater_2.php", "if(1 > 0)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_GREATER)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "greater_2.php")

TEST(test_greater_3, "Test greater 3")
int check = write_file("greater_3.php", "if(a > \"Saruman\")\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_GREATER)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.string, "Saruman") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "greater_3.php")

TEST(test_lesser_1, "Test lesser 1")
int check = write_file("lesser_1.php", "if(1 < c)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LESS)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "lesser_1.php")

TEST(test_lesser_2, "Test lesser 2")
int check = write_file("lesser_2.php", "if(1 < 0)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LESS)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "lesser_2.php")

TEST(test_lesser_3, "Test lesser 3")
int check = write_file("lesser_3.php", "if(a < \"Saruman\")\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LESS)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.string, "Saruman") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "lesser_3.php")

TEST(test_greater_equal_1, "Test greater_equal 1")
int check = write_file("greater_equal_1.php", "if(1 >= c)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_GREATER_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "greater_equal_1.php")

TEST(test_greater_equal_2, "Test greater_equal 2")
int check = write_file("greater_equal_2.php", "if(1 >= 0)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_GREATER_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "greater_equal_2.php")

TEST(test_greater_equal_3, "Test greater_equal 3")
int check =
	write_file("greater_equal_3.php", "if(a >= \"Saruman\")\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_GREATER_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.string, "Saruman") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "greater_equal_3.php")

TEST(test_lesser_equal_1, "Test lesser_equal 1")
int check = write_file("lesser_equal_1.php", "if(1 <= c)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LESS_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "lesser_equal_1.php")

TEST(test_lesser_equal_2, "Test lesser_equal 2")
int check = write_file("lesser_equal_2.php", "if(1 <= 0)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LESS_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "lesser_equal_2.php")

TEST(test_lesser_equal_3, "Test lesser_equal 3")
int check =
	write_file("lesser_equal_3.php", "if(a <= \"Saruman\")\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LESS_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.string, "Saruman") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "lesser_equal_3.php")

TEST(test_equal_1, "Test equal 1")
int check = write_file("equal_1.php", "if(1 === c)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "equal_1.php")

TEST(test_equal_2, "Test equal 2")
int check = write_file("equal_2.php", "if(1 === 0)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "equal_2.php")

TEST(test_equal_3, "Test equal 3")
int check = write_file("equal_3.php", "if(a === \"Saruman\")\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.string, "Saruman") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "equal_3.php")

TEST(test_not_equal_1, "Test not_equal 1")
int check = write_file("not_equal_1.php", "if(1 !== c)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_NOT_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "not_equal_1.php")

TEST(test_not_equal_2, "Test not_equal 2")
int check = write_file("not_equal_2.php", "if(1 !== 0)\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_NOT_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.number_int == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "not_equal_2.php")

TEST(test_not_equal_3, "Test not_equal 3")
int check =
	write_file("not_equal_3.php", "if(a !== \"Saruman\")\n{$var = c}\nelse \n{$brrrr = 42; }");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->value.keyword == KW_IF)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.identifier, "a") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_NOT_EQUAL)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(strcmp(token->value.string, "Saruman") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "var") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "c") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->value.keyword == KW_ELSE)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "brrrr") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 42)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "not_equal_3.php")

#ifndef LEX_ALL
int main(void)
{
    int tests_failed = 0;
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
    return tests_failed ? 1 : 0;
}
#endif // LEX_ALL
