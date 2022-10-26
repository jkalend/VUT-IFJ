#include "parser.h"
#include "scanner.h"
#include "stack.h"
#include "htab.h"


TData *stack_data(int value, int type){
    TData *ptr = malloc(sizeof(TData));
    if (ptr != NULL) {
        ptr->value = value;
        ptr->type = type;
    }
    return ptr;
}

int apply_rule(TStack *stack, unsigned int val) {
    switch (val) {
        case 0: exit(1); /* syntax error */
        case 1:
            stack_push(stack, stack_data(N_ST_LIST, T_NONTERM));
            stack_push(stack, stack_data(T_VALID, T_TERM));
            break;
        case 2:
            stack_push(stack, stack_data(N_ST_LIST, T_NONTERM));
            stack_push(stack, stack_data(N_ST, T_NONTERM));
            break;
        case 3:
            stack_push(stack, stack_data(T_EOF, T_TERM));
            break;
        case 4:
            stack_push(stack, stack_data(T_END, T_TERM));
            break;
        case 5:
            stack_push(stack, stack_data(T_RIGHT_BRACE, T_TERM));
            stack_push(stack, stack_data(N_BODY, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACE, T_TERM));
            stack_push(stack, stack_data(T_TYPE, T_TERM));
            stack_push(stack, stack_data(T_DOUBLE_DOT, T_TERM));
            stack_push(stack, stack_data(T_RIGHT_BRACKET, T_TERM));
            stack_push(stack, stack_data(N_PARAM_DEF, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACKET, T_TERM));
            stack_push(stack, stack_data(T_IDENTIFIER, T_TERM));
            stack_push(stack, stack_data(KW_FUNCTION, T_KW));
            break;
        case 6:
            stack_push(stack, stack_data(N_SMALL_ST, T_NONTERM));
            stack_push(stack, stack_data(T_VAR, T_TERM));
            stack_push(stack, stack_data(KW_GLOBAL, T_KW));
            break;
        case 7:
            stack_push(stack, stack_data(T_SEMICOLON, T_TERM));
            break;
        case 8:
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(T_IDENTIFIER, T_TERM));
            break;
        case 9:
            stack_push(stack, stack_data(N_SMALL_ST, T_NONTERM));
            stack_push(stack, stack_data(T_VAR, T_TERM));
            break;
        case 10:
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(KW_RETURN, T_KW));
            break;
        case 11:
            stack_push(stack, stack_data(T_RIGHT_BRACE, T_TERM));
            stack_push(stack, stack_data(N_BODY, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACE, T_TERM));
            stack_push(stack, stack_data(KW_ELSE, T_KW));
            stack_push(stack, stack_data(T_RIGHT_BRACE, T_TERM));
            stack_push(stack, stack_data(N_BODY, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACE, T_TERM));
            stack_push(stack, stack_data(T_RIGHT_BRACKET, T_TERM));
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACKET, T_TERM));
            stack_push(stack, stack_data(KW_IF, T_KW));
            break;
        case 12:
            stack_push(stack, stack_data(T_RIGHT_BRACE, T_TERM));
            stack_push(stack, stack_data(N_BODY, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACE, T_TERM));
            stack_push(stack, stack_data(T_RIGHT_BRACKET, T_TERM));
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACKET, T_TERM));
            stack_push(stack, stack_data(KW_WHILE, T_KW));
            break;
        case 13:
            stack_push(stack, stack_data(T_SEMICOLON, T_TERM));
            break;
        case 14:
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(T_ASSIGN, T_TERM));
            break;
        case 15:
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            break;
        case 16:
            stack_push(stack, stack_data(N_PARAM_LIST, T_NONTERM));
            stack_push(stack, stack_data(N_PARAM_NAME, T_NONTERM));
            stack_push(stack, stack_data(T_TYPE, T_TERM));
            break;
        case 17:
            stack_push(stack, stack_data(T_VAR, T_TERM));
            break;
        case 18:
            /* eps */
            break;
        case 19:
            stack_push(stack, stack_data(N_PARAM_DEF, T_NONTERM));
            stack_push(stack, stack_data(T_COMMA, T_TERM));
            break;
        case 20:
            stack_push(stack, stack_data(T_RIGHT_BRACKET, T_TERM));
            stack_push(stack, stack_data(N_PARAM_CALL, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACKET, T_TERM));
            stack_push(stack, stack_data(T_IDENTIFIER, T_TERM));
            break;
        case 21:
            stack_push(stack, stack_data(N_PARAM_CALL_LIST, T_NONTERM));
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            break;
        case 22:
            stack_push(stack, stack_data(N_PARAM_CALL, T_NONTERM));
            stack_push(stack, stack_data(T_COMMA, T_TERM));
            break;
        case 23:
            /* eps */
            break;
        case 24:
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            break;
        case 25:
            stack_push(stack, stack_data(N_BODY, T_NONTERM));
            stack_push(stack, stack_data(N_ST, T_NONTERM));
            break;
        case 26:
            /* eps */
            break;
        default: fprintf(stderr, "no rule found\n");
                 exit(1);
    }
    return 1;
}


int main() {
    stream = fopen("test.php", "r");
    if (stream == NULL) exit(1);


    TStack *stack;
    stack = stack_init(stack);
    
    TData *tmp = stack_data(T_EOF, T_TERM);
    TData *tmp2 = stack_data(N_PROG, T_NONTERM);
    stack_push(stack, tmp);
    stack_push(stack, tmp2);

    Token *token = malloc(sizeof(Token));
    if (token == NULL)  exit(1);

    get_token(token);
    while(1) {
        if (stack_isEmpty(stack)) {
            break;
        }

        TData *top = stack_pop(stack);
        if (top->type == T_TERM && top->value == token->type ||
            top->type == T_KW && token->type == T_KEYWORD && top->value == token->value.keyword) {
            get_token(token);
            continue;
        }
        else {
            fprintf(stderr, "terms not matching\n");
            exit(1);
        }

        if (top->type == T_NONTERM && top->value == N_EXPR) {
            /* call precedential */
        }
        unsigned int col_idx, row_idx;
        
        if (token->type == T_KEYWORD) {
            col_idx = token->value.keyword;
        }
        else col_idx = token->type;

        row_idx = top->value;

        unsigned int val = LL_TABLE[row_idx][col_idx];
       
        printf("%d ", val);
        apply_rule(stack, val);
    }
    printf("\n");
    stack_dispose(stack);
    return 0;
}