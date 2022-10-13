//
// Created by Kalenda, Jan on 02.10.2022.
//

#include "scanner.h"
#include "lex_all.h"
#include "error.h"
#include <stdlib.h>

TEST(test_empty, "Test empty file")
int check = write_file("empty_test_file.php", "");
if (check != 0) {
	return 1;
}
stream = fopen("empty_test_file.php", "r");
Token *token = malloc(sizeof(Token));
TEST_ASSERT(get_token(token) == 0)
TEST_ASSERT(token->type == T_EOF)
free(token);
ENDTEST(stream, "empty_test_file.php")

#ifndef LEX_ALL
int main(void) {
	return test_empty();
}
#endif	//LEX_ALL
