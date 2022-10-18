//
// Created by Kalenda, Jan on 17.10.2022.
//

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_prologue_exreme , "Test extreme prologue")
    int check = write_file("prologue_extreme_test_file.php",
                           "<?php //hello\t world\n"
                           "/*\n"
                            " * hello world\n"
                            " */\n"
                           "/*bye \\\"world*/declare   /*comment*/ //   \r\n  "
                           "(/*damn*/strict_types \t\n"
                           "  = \t /*oof*/   1/*comment*/\n\n\n"
                           ")\n\n\t\n\t\t;"
                           "/*\n"
                           " * hello world\n"
                           " */\n");
    if (check != 0) {
        return 1;
    }
    stream = fopen("prologue_extreme_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "prologue_extreme_test_file.php")


#ifndef LEX_ALL
int main(void) {
    return test_prologue_exreme();
}
#endif	//LEX_ALL
