//
// Created by Kalenda, Jan on 08.10.2022.
//

#include "scanner.h"
#include "error.h"
#include "lex_all.h"
#include <stdlib.h>

TEST(test_only_prologue, "Test only prologue")
    int check = write_file("only_prologue_test_file.php", "<?php");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_test_file.php")

TEST(test_only_prologue_with_spaces, "Test only prologue with spaces")
    int check = write_file("only_prologue_with_spaces_test_file.php", "<?php ");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_spaces_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_spaces_test_file.php")

TEST(test_only_prologue_with_newline, "Test only prologue with newline")
    int check = write_file("only_prologue_with_newline_test_file.php", "<?php\n");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_test_file.php")

TEST(test_only_prologue_with_newline_and_spaces, "Test only prologue with newline and spaces")
    int check = write_file("only_prologue_with_newline_and_spaces_test_file.php", "<?php\n   ");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_spaces_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_spaces_test_file.php")

TEST(test_only_prologue_with_newline_and_spaces_and_comment, "Test only prologue with newline and spaces and comment")
    int check = write_file("only_prologue_with_newline_and_spaces_and_comment_test_file.php",
                           "<?php\n   //comment");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_spaces_and_comment_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_spaces_and_comment_test_file.php")

TEST(test_only_prologue_with_newline_and_spaces_and_comment_and_newline,
     "Test only prologue with newline and spaces and comment and newline")
    int check = write_file("only_prologue_with_newline_and_spaces_and_comment_and_newline_test_file.php",
                           "<?php\n   //comment  ");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_spaces_and_comment_and_newline_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_spaces_and_comment_and_newline_test_file.php")

TEST(test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces,
     "Test only prologue with newline and spaces and comment and newline and spaces")
    int check = write_file("only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_test_file.php",
                           "<?php\n   //comment \n");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_test_file.php")

TEST(test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment,
     "Test only prologue with newline and spaces and comment and newline and spaces and comment")
    int check = write_file("only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment_test_file.php",
                           "<?php\n   //comment \n//comment");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment_test_file.php")

TEST(test_only_prologue_with_newline_and_block_comments, "Test only prologue with newline and block comments")
    int check = write_file("only_prologue_with_newline_and_block_comments_test_file.php",
                           "<?php\n/*comment*/");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_block_comments_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_block_comments_test_file.php")

TEST(test_only_prologue_with_newline_and_block_comments_and_newline,
        "Test only prologue with newline and block comments and newline")
    int check = write_file("only_prologue_with_newline_and_block_comments_and_newline_test_file.php",
                           "<?php\n/*comment*/\n");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_block_comments_and_newline_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_block_comments_and_newline_test_file.php")

TEST(test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces,
     "Test only prologue with newline and block comments and newline and spaces")
    int check = write_file("only_prologue_with_newline_and_block_comments_and_newline_and_spaces_test_file.php",
                           "<?php\n/*comment*/\n   ");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_block_comments_and_newline_and_spaces_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_block_comments_and_newline_and_spaces_test_file.php")

TEST(test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment,
     "Test only prologue with newline and block comments and newline and spaces and comment")
    int check = write_file("only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment_test_file.php",
                           "<?php\n/*comment*/\n   //comment");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment_test_file.php")

TEST(test_only_prologue_with_multiline_block_comment, "Test only prologue with multiline block comment")
    int check = write_file("only_prologue_with_multiline_block_comment_test_file.php",
                           "<?php\n/*comment\ncomment\ndamn*/");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_multiline_block_comment_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_multiline_block_comment_test_file.php")

TEST(test_only_prologue_with_declare, "Test only prologue with declare")
    int check = write_file("only_prologue_with_multiline_block_comment_and_newline_test_file.php",
                           "<?php\ndeclare(strict_types=1);");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_multiline_block_comment_and_newline_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)
    TEST_ASSERT(token->line == 1)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 6)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_IDENTIFIER)
    TEST_ASSERT(token->line == 2)
    TEST_ASSERT(token->column[0] == 1)
    TEST_ASSERT(token->column[1] == 8)
    TEST_ASSERT(strcmp(token->value.string, "declare") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_LEFT_BRACKET)
    TEST_ASSERT(token->line == 2)
    TEST_ASSERT(token->column[0] == 8)
    TEST_ASSERT(token->column[1] == 9)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_IDENTIFIER)
    TEST_ASSERT(token->line == 2)
    TEST_ASSERT(token->column[0] == 9)
    TEST_ASSERT(token->column[1] == 21)
    TEST_ASSERT(strcmp(token->value.string, "strict_types") == 0)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EQUAL)
    TEST_ASSERT(token->line == 2)
    TEST_ASSERT(token->column[0] == 21)
    TEST_ASSERT(token->column[1] == 22)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_INT)
    TEST_ASSERT(token->line == 2)
    TEST_ASSERT(token->column[0] == 22)
    TEST_ASSERT(token->column[1] == 23)
    TEST_ASSERT(token->value.number_int == 1)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_RIGHT_BRACKET)
    TEST_ASSERT(token->line == 2)
    TEST_ASSERT(token->column[0] == 23)
    TEST_ASSERT(token->column[1] == 24)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_SEMICOLON)
    TEST_ASSERT(token->line == 2)
    TEST_ASSERT(token->column[0] == 24)
    TEST_ASSERT(token->column[1] == 25)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_multiline_block_comment_and_newline_test_file.php")

#ifndef LEX_ALL
int main(void) {
    int tests_failed = 0;
    tests_failed += test_only_prologue();
    tests_failed += test_only_prologue_with_spaces();
    tests_failed += test_only_prologue_with_newline();
    tests_failed += test_only_prologue_with_newline_and_spaces();
    tests_failed += test_only_prologue_with_newline_and_spaces_and_comment();
    tests_failed += test_only_prologue_with_newline_and_spaces_and_comment_and_newline();
    tests_failed += test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces();
    tests_failed += test_only_prologue_with_newline_and_spaces_and_comment_and_newline_and_spaces_and_comment();
    tests_failed += test_only_prologue_with_newline_and_block_comments();
    tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline();
    tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces();
    tests_failed += test_only_prologue_with_newline_and_block_comments_and_newline_and_spaces_and_comment();
    tests_failed += test_only_prologue_with_multiline_block_comment();
    //tests_failed += test_only_prologue_with_declare(); //TODO SIGSEGVs as of now due to strcmp
    return tests_failed ? 1 : 0;
}
#endif //LEX_ALL
