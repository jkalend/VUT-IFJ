//
// Created by Jarek on 17.11.2022.
//

#include "scanner.h"
#include "lex_all.h"
#include "error.h"
#include <stdlib.h>

TEST(test_faulty_declare, "Test faulty declare")
int check = write_file("faulty_declare.php",
					   "<?phpdeclare(strict_types=1)\n<?phf declare(strict_types=1)\n<?ahp declare(strict_types=1)\n<?pvp declare(strict_types=1)\n<?php decl4re(strict_types=1)"
					   "\n<?php declare(strict_tipes=1)\n<?php declare(strict_types+1)\n<?php declare(strict_types=3)\n"
					   );
if (check != 0) {
	return 1;
}
stream = fopen("faulty_declare.php", "r");
Token *token = malloc(sizeof(Token));
first_read = 1;

TEST_ASSERT(get_token(token) != 0)
int a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->type == T_ERROR)



TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 5)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 6)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 7)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 8)
TEST_ASSERT(token->type == T_ERROR)

ENDTEST(stream, "faulty_declare.php")

TEST(test_faulty_type, "Test faulty type")
int check = write_file("faulty_type.php", "?stringint\n?Int\nfloating\n");
if (check != 0) {
	return 1;
}
stream = fopen("faulty_type.php", "r");
Token *token = malloc(sizeof(Token));
first_read = 1;

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
int a = fgetc(stream);
while(a != '\n') {
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->type == T_IDENTIFIER)

ENDTEST(stream, "faulty_type.php")

/*
TEST(test_faulty_identifier, "Test faulty identifier")
int check = write_file("faulty_identifier.php", "7lmao\n__&cus\nnevim£\nÃhoj\n");
if (check != 0) {
	return 1;
}
stream = fopen("faulty_identifier.php", "r");
Token *token = malloc(sizeof(Token));
first_read = 1;

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->value.number_int == 7)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->type == T_IDENTIFIER)
TEST_ASSERT(strcmp(token->value.identifier, "lmao") == 0)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_IDENTIFIER)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_IDENTIFIER)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->type == T_ERROR)

ENDTEST(stream, "faulty_identifier.php")


TEST(test_faulty_variable, "Test faulty variable")
int check = write_file("faulty_variable.php", "$7lmao\n$__&cus\n$nevim£\n$Ãhoj\n");
if (check != 0) {
	return 1;
}
stream = fopen("faulty_variable.php", "r");
Token *token = malloc(sizeof(Token));
first_read = 1;

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->type == T_ERROR)

ENDTEST(stream, "faulty_variable.php")
 */

TEST(test_faulty_number, "Test faulty number")
int check = write_file("faulty_number.php", "13e\n7^4\n13.\n3ee7\n21.e.7\n22e+-9\n9Ee\n5E5.5\n3.a6\n7e.7\n4.e9\n");
if (check != 0) {
	return 1;
}
stream = fopen("faulty_number.php", "r");
Token *token = malloc(sizeof(Token));
first_read = 1;

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->value.number_int == 7)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_INT)
TEST_ASSERT(token->value.number_int == 4)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 5)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 6)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 7)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 8)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
int a = fgetc(stream);
while(a != '\n'){
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 9)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 10)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 11)
TEST_ASSERT(token->type == T_ERROR)

ENDTEST(stream, "faulty_number.php")

TEST(test_faulty_characters_and_combinations, "Test faulty characters and combinations")
int check = write_file("faulty_characters_and_combinations.php", "==\n!=\n&&\n||\n!\n[\n]\n");
if (check != 0) {
	return 1;
}
stream = fopen("faulty_characters_and_combinations.php", "r");
Token *token = malloc(sizeof(Token));
first_read = 1;

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 1)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 2)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
int a = fgetc(stream);
while(a != '\n'){
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 3)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
a = fgetc(stream);
while(a != '\n'){
	a = fgetc(stream);
}
line++;
TEST_ASSERT(token->line == 4)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 5)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 6)
TEST_ASSERT(token->type == T_ERROR)

TEST_ASSERT(get_token(token) != 0)
TEST_ASSERT(token->line == 7)
TEST_ASSERT(token->type == T_ERROR)

ENDTEST(stream, "faulty_characters_and_combinations.php")

#ifndef LEX_ALL
int main(void) {
	int tests_failed = 0;
	tests_failed += test_faulty_declare();
	//tests_failed += test_faulty_identifier();
	//tests_failed += test_faulty_variable();
	tests_failed += test_faulty_type();
	tests_failed += test_faulty_number();
	tests_failed += test_faulty_characters_and_combinations();
	return tests_failed ? 1 : 0;
}
#endif	//LEX_ALL