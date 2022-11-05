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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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
    TEST_ASSERT(get_token(token) != 0)
    TEST_ASSERT(token->type == T_ERROR)
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

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_multiline_block_comment_and_newline_test_file.php")

TEST(test_only_prologue_with_comments_and_declare,
     "Test only prologue with comments and declare")
    int check = write_file("only_prologue_with_comments_and_declare_test_file.php",
                           "<?php declare(strict_types=1);");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_comments_and_declare_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_comments_and_declare_test_file.php")

TEST(test_only_prologue_with_block_comments_and_declare,
     "Test only prologue with block comments and declare")
    int check = write_file("only_prologue_with_block_comments_and_declare_test_file.php",
                           "<?php\n/*comment*/\ndeclare(strict_types=1);");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_block_comments_and_declare_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_block_comments_and_declare_test_file.php")

TEST(test_only_prologue_with_block_comments_in_declare,
    "Test only prologue with block comments in declare")
    int check = write_file("only_prologue_with_block_comments_in_declare_test_file.php",
                        "<?php\ndeclare(strict_types=1/*comment*/);");
    if (check != 0) {
        return 1;
    }
        stream = fopen("only_prologue_with_block_comments_in_declare_test_file.php", "r");
        Token *token = malloc(sizeof(Token));
        TEST_ASSERT(get_token(token) == 0)
        TEST_ASSERT(token->type == T_VALID)

        TEST_ASSERT(get_token(token) == 0)
        TEST_ASSERT(token->type == T_EOF)
        free(token);
ENDTEST(stream, "only_prologue_with_block_comments_in_declare_test_file.php")

TEST(test_only_prologue_with_more_block_comments_in_declare,
    "Test only prologue with more block comments in declare")
    int check = write_file("only_prologue_with_more_block_comments_in_declare_test_file.php",
                        "<?php\ndeclare(strict_types=1/*comment*/\n/*comment*/);");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_more_block_comments_in_declare_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_more_block_comments_in_declare_test_file.php")

TEST(test_only_prologue_with_multiline_block_comments_in_declare,
    "Test only prologue with multiline block comments in declare")
    int check = write_file("only_prologue_with_multiline_block_comments_in_declare_test_file.php",
                        "<?php\ndeclare(strict_types=1/*comment\ncomment\ndamn*/);");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_multiline_block_comments_in_declare_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_multiline_block_comments_in_declare_test_file.php")

TEST(test_only_prologue_with_multiline_block_comments_before_declare,
    "Test only prologue with multiline block comments before declare")
    int check = write_file("only_prologue_with_multiline_block_comments_before_declare_test_file.php",
                        "<?php\n/*co\nmm\nen\nt\ncom\nme\nnt\nda\nmn*/\ndeclare(strict_types=1);");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_multiline_block_comments_before_declare_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_multiline_block_comments_before_declare_test_file.php")

TEST(test_only_prologue_with_multiline_block_comments_after_declare,
    "Test only prologue with multiline block comments after declare")
    int check = write_file("only_prologue_with_multiline_block_comments_after_declare_test_file.php",
                        "<?php\ndeclare(strict_types=1);\n/*co\nmm\nen\nt\ncom\nme\nnt\nda\nmn*/");
    if (check != 0) {
        return 1;
    }
    stream = fopen("only_prologue_with_multiline_block_comments_after_declare_test_file.php", "r");
    Token *token = malloc(sizeof(Token));
    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_VALID)

    TEST_ASSERT(get_token(token) == 0)
    TEST_ASSERT(token->type == T_EOF)
    free(token);
ENDTEST(stream, "only_prologue_with_multiline_block_comments_after_declare_test_file.php")

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
    tests_failed += test_only_prologue_with_declare();
    tests_failed += test_only_prologue_with_comments_and_declare();
    tests_failed += test_only_prologue_with_block_comments_and_declare();
    tests_failed += test_only_prologue_with_more_block_comments_in_declare();
    tests_failed += test_only_prologue_with_multiline_block_comments_in_declare();
    tests_failed += test_only_prologue_with_multiline_block_comments_before_declare();
    tests_failed += test_only_prologue_with_multiline_block_comments_after_declare();
    return tests_failed ? 1 : 0;
}
#endif //LEX_ALL
