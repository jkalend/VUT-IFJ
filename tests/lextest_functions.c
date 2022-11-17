// lextest_functions.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 19.10.2022
// Přeloženo: gcc 9.4.0

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_func_definition_1, "Test function definition 1")
int check = write_file("func_definition_1.php",
					   "<?phwp declare(strict_types=1);\nfunction foo(int $n) : int {}");
if (check != 0) {
	return 1;
}
stream = fopen("func_definition_1.php", "r");
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_FUNCTION)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "foo") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_INT)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "n") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DOUBLE_DOT)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_INT)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "func_definition_1.php")

TEST(test_func_definition_2, "Test function definition 2")
int check = write_file(
	"func_definition_2.php",
	"<?phwp declare(strict_types=1);\nfunction foo(int $n) : int {\nGandalf = \"The Gray Wizard\";\nreturn 1;}");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_FUNCTION)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "foo") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_INT)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "n") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DOUBLE_DOT)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_INT)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "Gandalf") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.string, "The Gray Wizard") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.keyword == KW_RETURN)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "func_definition_2.php")

TEST(test_func_definition_3, "Test function definition 3")
int check = write_file(
	"func_definition_3.php",
	"<?phwp declare(strict_types=1);\nfunction foo(int $n) : string {\nGandalf = \"The Gray Wizard\"\ntemp = n;\nreturn $Gandalf;\n}");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_FUNCTION)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "foo") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_INT)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "n") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_DOUBLE_DOT)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->value.keyword == KW_INT)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACE)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.identifier, "Gandalf") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_STRING)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(strcmp(token->value.string, "The Gray Wizard") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 3)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "temp") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(strcmp(token->value.identifier, "n") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 4)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_KEYWORD)
TEST_ASSERT(token->line == 5)
TEST_ASSERT(token->value.keyword == KW_RETURN)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->line == 5)
TEST_ASSERT(token->value.number_int == 1)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_RIGHT_BRACE)
TEST_ASSERT(token->line == 6)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "func_definition_3.php")

//----------------------------------------------
//----------------------------------------------
//----------------------------------------------

TEST(test_func_call_1, "Test function call 1")
int check =
	write_file("func_call_1.php", "<?phwp declare(strict_types=1);\n$result = foo($variable);");
if (check != 0) {
	return 1;
}
Token *token = malloc(sizeof(Token));

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VALID)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "result") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_ASSIGN)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "foo") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_LEFT_BRACKET)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_VAR)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(strcmp(token->value.identifier, "variable") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_SEMICOLON)
TEST_ASSERT(token->line == 2)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)

free(token);
ENDTEST(stream, "func_call_1.php")

#ifndef LEX_ALL
int main(void)
{
    int tests_failed = 0;
    tests_failed += test_func_definition_1();
    tests_failed += test_func_definition_2();
    tests_failed += test_func_definition_3();
    tests_failed += test_func_call_1();
    return tests_failed ? 1 : 0;
}
#endif // LEX_ALL
