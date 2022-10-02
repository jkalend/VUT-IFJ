//
// Created by Kalenda, Jan on 02.10.2022.
//

#include "scanner.h"
#include "error.h"
#include <stdlib.h>
#include <assert.h>

int main(void) {
    stream = fopen("empty_test_file.txt", "w");
    fclose(stream);
    stream = fopen("empty_test_file.txt", "r");
    Token *token = malloc(sizeof(Token));
    assert(get_token(token) == BAD_SYNTAX);
    assert(token->type == T_EOF);
    free(token);
    fclose(stream);
}
