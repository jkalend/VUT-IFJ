#include "parser.h"
#include "scanner.h"
#include "stack.h"
#include "symtable.h"
#include "error.h"
#include "math.h"
#include "generator.h"

/* global struct for parser flags and variables */
parser_t parser;

const unsigned int PREC_TABLE[14][14] = {
        {P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_OPEN, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_CLOSE},
        {P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_OPEN, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_CLOSE},
        {P_OPEN,P_OPEN,P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_OPEN, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_CLOSE},
        {P_OPEN,P_OPEN,P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_OPEN, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_CLOSE},
        {P_OPEN,P_OPEN,P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_OPEN, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_CLOSE},
        {P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, [7] = P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, [13] = P_CLOSE},
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_EQUAL, P_OPEN, P_OPEN, P_OPEN, [12] = P_OPEN, P_EQUAL},
        {P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, [7] = P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, P_CLOSE, [13] = P_CLOSE},
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_CLOSE, [9] = P_CLOSE, P_CLOSE, P_CLOSE, P_OPEN, P_CLOSE},
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_CLOSE, P_OPEN, [11] = P_CLOSE, P_OPEN, P_CLOSE},
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_CLOSE, P_OPEN, [11] = P_CLOSE, P_OPEN, P_CLOSE},
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, [8] = P_OPEN, P_OPEN, P_OPEN, [12] = P_OPEN},
        {[6] = P_EQUAL},
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN,P_OPEN, P_OPEN, P_EQUAL, P_OPEN, [12] = P_OPEN, P_EQUAL}
};

const unsigned int LL_TABLE[8][33] = {{1},
                                      {0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 0, 3, 4, [15] =  2, 2, 2, 2},
                                      {0, 7, 11, 12, 10, 5, 6, 9, 0, 0, [15] =  7, 7, 7, 7},
                                      {[9] = 15, 14, [19] = 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15},
                                      {[8] = 16, [14] = 22},
                                      {[7] = 17},
                                      {[11] = 19, [14] = 18},
                                      {0, 20, 20, 20, 20, 0, 20, 20, 0, 20, 0, 0, 0, 0, 21, [15] =  20, 20, 20, 20} };


TData *stack_data(int value, int type) { //unsigned?
    TData *ptr = malloc(sizeof(TData));
    if (ptr != NULL) {
        ptr->value = value;
        ptr->type = type;
        ptr->htab = NULL;
        ptr->bucket = NULL;
    }
    return ptr;
}

void defvar_order(char *id, htab_pair_t *pair, Generator *gen) {
    if (parser.in_while == NULL && !parser.in_function) {
        generator_add_instruction(gen, gen_instruction_constructor(defvar, id, NULL, NULL, 0, NULL, 0));
    } else if (parser.in_function) {
        parser.in_fn->operands = realloc(parser.in_fn->operands, sizeof(htab_pair_t *) * (parser.in_fn->operands_count + 1));
        if (parser.in_fn->operands == NULL) exit(BAD_INTERNAL);
        parser.in_fn->operands[parser.in_fn->operands_count++ ] = pair;
    } else if (parser.in_while != NULL) {
        parser.in_while->operands = realloc(parser.in_while->operands, sizeof(htab_pair_t *) * (parser.in_while->operands_count + 1));
        if (parser.in_while->operands == NULL) exit(BAD_INTERNAL);
        parser.in_while->operands[parser.in_while->operands_count++ ] = pair;
    }
}

void get_next_token(Token **token, bool *keep_token, bool *return_back) {
    if (*keep_token && *return_back) {
        Token *tmp = *token;
        *token = parser.tmp_token;
        parser.tmp_token = tmp;
    }
    else if (!(*keep_token) && *return_back) {
        Token *tmp = *token;
        *token = parser.tmp_token;
        parser.tmp_token = tmp;
        *return_back = false;
    }
    else if (!(*keep_token)){
        /* copy previous token to temporary token */
        parser.tmp_token->line = (*token)->line;
        parser.tmp_token->value = (*token)->value;
        parser.tmp_token->type = (*token)->type;

        /* get new token from scanner */
        get_token(*token);
        if ((*token)->type == T_ERROR) exit(BAD_LEXEM);
    }
    *keep_token = false;
}

int apply_rule(TStack *stack, unsigned int val) {
    switch (val) {
        case 0: exit(BAD_SYNTAX); /* syntax error */
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
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            break;
        case 8:
            stack_push(stack, stack_data(T_SEMICOLON, T_TERM));
            break;
        case 9:
            stack_push(stack, stack_data(N_SMALL_ST, T_NONTERM));
            stack_push(stack, stack_data(T_VAR, T_TERM));
            break;
        case 10:
            stack_push(stack, stack_data(T_SEMICOLON, T_TERM));
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
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(KW_IF, T_KW));
            break;
        case 12:
            stack_push(stack, stack_data(T_RIGHT_BRACE, T_TERM));
            stack_push(stack, stack_data(N_BODY, T_NONTERM));
            stack_push(stack, stack_data(T_LEFT_BRACE, T_TERM));
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(KW_WHILE, T_KW));
            break;
        case 13:
            stack_push(stack, stack_data(T_SEMICOLON, T_TERM));
            break;
        case 14:
            stack_push(stack, stack_data(T_SEMICOLON, T_TERM));
            stack_push(stack, stack_data(N_EXPR, T_NONTERM));
            stack_push(stack, stack_data(T_ASSIGN, T_TERM));
            break;
        case 15:
            stack_push(stack, stack_data(T_SEMICOLON, T_TERM));
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
            stack_push(stack, stack_data(N_BODY, T_NONTERM));
            stack_push(stack, stack_data(N_ST, T_NONTERM));
            break;
        
        case 21:
        case 22:
            /* eps */
            break;
        default: /* no rule found */
            exit(BAD_SYNTAX);
    }
    return 1;
}

void prec_index(const Token *token, unsigned int *rc, int symbol) {
    if (symbol > -1 && symbol < 15) {
        *rc = symbol;
        return;
    }
    switch (token->type) {

        case T_IDENTIFIER: //func
            *rc = 12;
            break;
        case T_STRING: case T_INT: case T_FLOAT: case T_VAR:
            *rc = 5;
            break;
        case T_COMMA:
            *rc = 13;
            break;
        case T_EOF: case T_END:
            exit(BAD_SYNTAX);
        case T_PLUS:
            *rc = 2;
            break;
        case T_MINUS:
            *rc = 3;
            break;
        case T_CONCATENATE:
            *rc = 4;
            break;
        case T_MULTIPLY:
            *rc = 0;
            break;
        case T_DIVIDE:
            *rc = 1;
            break;
        case T_LESS: case T_LESS_EQUAL: case T_GREATER: case T_GREATER_EQUAL:
            *rc = 8;
            break;
        case T_EQUAL:
            *rc = 9;
            break;
        case T_NOT_EQUAL:
            *rc = 10;
            break;
        case T_LEFT_BRACKET:
            *rc = 6;
            break;
        case T_RIGHT_BRACKET:
            *rc = 7;
            break;
        case T_ERROR:
            exit(BAD_LEXEM);
        case T_SEMICOLON: case T_LEFT_BRACE:
            break;
        case T_KEYWORD:
            if (token->value.keyword == KW_NULL) {
                *rc = 5;
            } else {
                exit(BAD_SYNTAX);
            }
            break;
        default:
            exit(BAD_SYNTAX);
    }
}

int reduce(TStack *stack, TStack *shelf, TStack *temps, Generator *gen, bool end) {

    if (stack_top(stack)->value == P_E) {
        stack_push(shelf, stack_pop(stack));
        if (stack_top(stack)->value == P_END) {
            stack_push(stack, stack_pop(shelf));
            return -1; //empty expr
        }
    }
    unsigned int res = 0;
    bool fn = false;
    htab_pair_t *last_fn = NULL;

    while (stack_top(stack)->value != P_OPEN && stack_top(stack)->value != P_END) {
        TData *data = stack_pop(stack);
        stack_push(shelf, data);
        res += data->value;
        if (data->value == P_FN) {
            fn = true;
            last_fn = data->bucket;
        }
    }
    if (stack_top(stack)->value == P_OPEN) {
        const TData *data = stack_pop(stack);
        res += data->value;
        stack_push(shelf, data);
    } else if (stack_top(stack)->value == P_END && end) {
        return -1;
    } else if (stack_top(stack)->value == P_END && !end) {
        exit(BAD_SYNTAX);
    }

    int cnt = 0;
    TData *op_one;
    TData *op_two;
    htab_pair_t **operands = NULL;

    long long number_size = (long long) ((ceil(log10(parser.tmp_counter)) + 1) * sizeof(char));
    size_t alloc_num = snprintf(NULL, 0, "%d", parser.tmp_counter);
    char *number = malloc(alloc_num);
    if (number == NULL) exit(BAD_INTERNAL);
    snprintf(number, number_size, "%d", parser.tmp_counter);

    char *tmp = malloc(sizeof(char) * (TEMP_LENGTH + alloc_num));
    if (tmp == NULL) exit(BAD_INTERNAL);
    strncpy(tmp, TEMP_VAR_PREFIX, TEMP_LENGTH);
    strncat(tmp, number, sizeof(char) * (TEMP_LENGTH + alloc_num));

    TData *data = NULL;
    htab_pair_t *pair = NULL;
    if (res > 34 && res != 59) {
        parser.tmp_counter++;
        pair = htab_insert(parser.temporary_tab, NULL, tmp);
        data = stack_data(P_E, P_E);
        data->bucket = pair;
        data->bucket->type = H_VAR;
    }

    if (fn) {
        if (data == NULL) {
            exit(BAD_SYNTAX);
        }
        data->bucket->type = H_FUNC_ID;
        //symtable is used here to check for number of args
        int brackets = 0;
        int E = 0;
        int commas = 0;
        int previous_args = 0;
        TStack *reversal = NULL;
        reversal = stack_init(reversal);

        if (last_fn->return_type == D_NONE && last_fn->param_count != 0) {
            previous_args = last_fn->param_count;
            last_fn->param_count = 0;
        }

        bool expect_comma = false;

        while (stack_top(shelf)->value != P_CLOSE) {
            TData *tmp_data = stack_pop(shelf);
            htab_pair_t *a = tmp_data->bucket;
            if (tmp_data->value == P_LEFT_BRACKET) brackets--;
            else if (tmp_data->value == P_RIGHT_BRACKET) brackets++;
            else if (tmp_data->value == P_E) {
                E++;
                expect_comma = true;
                //free(tmp_data);
                tmp_data = stack_pop(temps);
                stack_push(reversal, tmp_data);
                if (last_fn->return_type == D_NONE) {
                    last_fn->params = realloc(last_fn->params, sizeof(DataType) * E);
                    last_fn->params[last_fn->param_count++] = tmp_data->bucket->value_type;
                }
            } else if (tmp_data->value == P_COMMA) {
                if(!expect_comma) exit(BAD_SYNTAX);
                commas++;
                expect_comma = false;
            }
            else {
                free(tmp_data);
            }
        }
        if (brackets != 0) exit(BAD_SYNTAX);
        if (stack_top(shelf) != NULL) { // pops last bracket
            free(stack_pop(shelf));
        }

        // args number check
        if (E != last_fn->param_count && last_fn->param_count != -1 && last_fn->return_type != D_NONE)  {
            exit(BAD_TYPE_OR_RETURN);
        }
        if (E != previous_args && previous_args != 0) {
            exit(BAD_TYPE_OR_RETURN);
        }

        if (commas != E - 1 && E != 0) exit(BAD_SYNTAX);

        int builtin = -1;
        for (int j = 0; j < 11; j++) {
            if(strcmp(last_fn->identifier, parser.builtins[j]) == 0) {
                builtin = j;
                break;
            }
        }

        htab_pair_t **params = NULL;
        if (builtin != -1) {
            data->bucket->type = H_VAR;
            defvar_order(tmp, pair, gen);

            params = E ? malloc(sizeof(htab_pair_t*) * E) : malloc(sizeof(htab_pair_t*));
            for (int j = 0; j < E; j++) {
                TData *garbage = stack_pop(reversal);
                params[j] = garbage->bucket;
                free(garbage);
            }

            generator_add_instruction(gen, gen_instruction_constructor(builtin, tmp, operands, NULL, 0, params, E));
        } else {
            // creates a temporary variable
            defvar_order(tmp, pair, gen);

            // prepares the call instruction
            operands = malloc(sizeof(htab_pair_t *));
            operands[0] = last_fn;
            params = malloc(sizeof(htab_pair_t*) * last_fn->param_count);
            for (int i = 0; i < last_fn->param_count; i++) {
                TData *garbage = stack_pop(reversal);
                params[i] = garbage->bucket;
                free(garbage);
            }
            generator_add_instruction(gen, gen_instruction_constructor(call, tmp, operands, last_fn->params, 1, params, last_fn->param_count));
        }

        printf("11p ");
        stack_push(stack, stack_data(P_E, P_E));
        data->bucket->value_type = last_fn->return_type;
        stack_push(temps, data);
        return 1;
    }

    switch (res) {
        case 34: // <i>
            while (cnt < 3) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 3) break;
            stack_push(stack, stack_data(P_E, P_E));
            printf("1p ");
            return 1;
        case 54:
            exit(BAD_SYNTAX);
        case 63: // multiplication
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);

            // type of the outcome
            if (op_one->bucket->value_type == D_FLOAT || op_two->bucket->value_type == D_FLOAT) {
                pair->value_type = D_FLOAT;
            } else if (op_one->bucket->value_type == D_INT && op_two->bucket->value_type == D_INT) {
                pair->value_type = D_INT;
            } else if (op_one->bucket->value_type == D_VOID && op_two->bucket->value_type == D_VOID) {
                pair->value_type = D_INT;
            }

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[0] = op_one->bucket; // order doesn't matter here
            operands[1] = op_two->bucket;
            generator_add_instruction(gen, gen_instruction_constructor(mul, tmp, operands, NULL, 2, NULL, 0));

            free(op_one);
            free(op_two);

            printf("2p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            return 1;
        case 64: // division
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);
            pair->value_type = D_FLOAT;

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[1] = op_one->bucket; //reversed due to stack
            operands[0] = op_two->bucket;
            generator_add_instruction(gen, gen_instruction_constructor(div_, tmp, operands, NULL, 2, NULL, 0));

            free(op_one);
            free(op_two);

            printf("3p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            return 1;
        case 65: // addition
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);

            // type of the outcome
            if (op_one->bucket->value_type == D_FLOAT || op_two->bucket->value_type == D_FLOAT) {
                pair->value_type = D_FLOAT;
            } else if (op_one->bucket->value_type == D_INT && op_two->bucket->value_type == D_INT) {
                pair->value_type = D_INT;
            } else if (op_one->bucket->value_type == D_VOID && op_two->bucket->value_type == D_VOID) {
                pair->value_type = D_INT;
            }

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[1] = op_one->bucket; //reversed due to stack
            operands[0] = op_two->bucket;
            generator_add_instruction(gen, gen_instruction_constructor(addition, tmp, operands, NULL, 2, NULL, 0));

            free(op_one);
            free(op_two);

            printf("4p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            return 1;
        case 66: // subtraction
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);

            // type of the outcome
            if (op_one->bucket->value_type == D_FLOAT || op_two->bucket->value_type == D_FLOAT) {
                pair->value_type = D_FLOAT;
            } else if (op_one->bucket->value_type == D_INT && op_two->bucket->value_type == D_INT) {
                pair->value_type = D_INT;
            } else if (op_one->bucket->value_type == D_VOID && op_two->bucket->value_type == D_VOID) {
                pair->value_type = D_INT;
            }

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[1] = op_one->bucket; //reversed due to stack
            operands[0] = op_two->bucket;
            generator_add_instruction(gen, gen_instruction_constructor(sub, tmp, operands, NULL, 2, NULL, 0));

            free(op_one);
            free(op_two);

            printf("5p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            return 1;
        case 67: // concatenation
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[1] = op_one->bucket; //reversed due to stack
            operands[0] = op_two->bucket;
            generator_add_instruction(gen, gen_instruction_constructor(concat, tmp, operands, NULL, 2, NULL, 0));

            free(op_one);
            free(op_two);

            pair->value_type = D_STRING;

            printf("6p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            return 1;
        case 59: // brackets
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            printf("7p ");
            stack_push(stack, stack_data(P_E, P_E));
            return 1;
        case 71: // relations or a function
            //if (fn) goto function;
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);
            pair->value_type = D_BOOL;

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[1] = op_one->bucket; //reversed due to stack
            operands[0] = op_two->bucket;
            Instruction *rel = gen_instruction_constructor(div_, tmp, operands, NULL, 2, NULL, 0);

            switch (parser.relation_operator) {
                case T_GREATER:
                    rel->instruct = gt;
                    break;
                case T_LESS:
                    rel->instruct = lt;
                    break;
                case T_GREATER_EQUAL:
                    rel->instruct = gte;
                    break;
                case T_LESS_EQUAL:
                    rel->instruct = lte;
                    break;
                default:
                    exit(BAD_SYNTAX);
            }

            generator_add_instruction(gen, rel);

            free(op_one);
            free(op_two);

            printf("8p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            parser.relation_operator = 0;
            return 1;
        case 72: // E===E
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);
            pair->value_type = D_BOOL;

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[1] = op_one->bucket; //reversed due to stack
            operands[0] = op_two->bucket;
            generator_add_instruction(gen, gen_instruction_constructor(eq, tmp, operands, NULL, 2, NULL, 0));

            free(op_one);
            free(op_two);

            printf("9p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            parser.relation_operator = 0;
            return 1;
        case 73: // E!==E
            while (cnt < 5) {
                TData *garbage = stack_pop(shelf);
                if (garbage == NULL) {
                    break;
                }
                free(garbage);
                cnt++;
            }
            if (cnt != 5) break;
            op_one = stack_pop(temps);
            op_two = stack_pop(temps);
            pair->value_type = D_BOOL;

            defvar_order(tmp, pair, gen);

            operands = malloc(sizeof(htab_pair_t*) * 2);
            operands[1] = op_one->bucket; //reversed due to stack
            operands[0] = op_two->bucket;
            generator_add_instruction(gen, gen_instruction_constructor(neq, tmp, operands, NULL, 2, NULL, 0));

            free(op_one);
            free(op_two);

            printf("10p ");
            stack_push(temps, data);
            stack_push(stack, stack_data(P_E, P_E));
            parser.relation_operator = 0;
            return 1;
        default:
            //if (fn) goto function;
            break;
    }

    free(data);
    stack_dispose(shelf);
    return 0;
}

int precedence(TStack *stack, Token **token, bool *keep_token, bool *return_back, Generator *gen) {
    stack_push(stack, stack_data(P_END, P_END));
    
    Token *lookahead = *token;
    bool end = false;
    bool next_token = true;
    bool ID_last_token = false;
    parser.empty_expr = false;
    unsigned int row = 0;
    unsigned int column = 0;
    TStack *shelf = NULL;
    TStack *temps = NULL;
    shelf = stack_init(shelf);
    temps = stack_init(temps);
    while (true) {

        if (next_token) {
            get_next_token(&lookahead, keep_token, return_back);
            if (lookahead->type == T_ERROR) break;

            next_token = true;

            if (ID_last_token == true && lookahead->type != T_LEFT_BRACKET) {
                exit(BAD_SYNTAX);
            } else {
                ID_last_token = false;
            }
        }

        if (parser.only_defvar && lookahead->type != T_SEMICOLON) {
            parser.only_defvar = false;
        }

        if (lookahead->type == T_LEFT_BRACE || lookahead->type == T_SEMICOLON) {
            end = true;
            *token = lookahead;
            *keep_token = true;
        }
        
        
        //only 1 skip needed?
        if (stack_top(stack)->value == P_E) stack_push(shelf, stack_pop(stack));

        //gets indexes for the table
        prec_index(NULL, &row,  (int)stack_top(stack)->value);
        if (!end) {
            prec_index(lookahead, &column, -1);
        } else {
            prec_index(NULL, &column, P_END);
        }
        
        unsigned int sym = PREC_TABLE[row][column];
        if (!sym && !end) {
            exit(BAD_SYNTAX);
        }
        if (sym != P_EQUAL && !end) { // skips equal signs
            if (sym == P_CLOSE) {
                while (!stack_isEmpty(shelf)) {
                    stack_push(stack, stack_pop(shelf));
                }
            }
            stack_push(stack, stack_data((int) sym, (int) sym));
        }

        bool end_E = stack_top(stack)->type == P_END && end;
        while (!stack_isEmpty(shelf)) {
            stack_push(stack, stack_pop(shelf));
        }
        if (end && !end_E) stack_push(stack, stack_data(P_CLOSE, P_CLOSE));

        if (sym == P_CLOSE) {
            int res = reduce(stack, shelf, temps, gen, end);
            if (!res || !stack_isEmpty(shelf)) {
                exit(BAD_SYNTAX);
            }
            next_token = false;
            continue;
        }

        // reduction happened, new token will be required
        next_token = true;

        if (!end) {
            long long number_size = (long long) ((ceil(log10(parser.tmp_counter)) + 1) * sizeof(char));
            size_t alloc_num = snprintf(NULL, 0, "%d", parser.tmp_counter);
            char *number = malloc(alloc_num);
            if (number == NULL) exit(BAD_INTERNAL);
            snprintf(number, number_size, "%d", parser.tmp_counter);

            char *tmp = malloc(sizeof(char) * (TEMP_LENGTH + alloc_num));
            if (tmp == NULL) exit(BAD_INTERNAL);
            strcpy(tmp, TEMP_VAR_PREFIX);
            strcat(tmp, number);

            htab_pair_t **operands = NULL;

            if (lookahead->type == T_IDENTIFIER) {
                char *id = malloc(strlen(lookahead->value.identifier) + 3);
                if (id == NULL) exit(BAD_INTERNAL);
                strcpy(id, "69");
                strcat(id, lookahead->value.identifier);

                htab_pair_t *pair = htab_find(parser.glob_tab, id);
                TData *data = stack_data(P_FN, P_FN);
                
                if (pair == NULL) {      
                    pair = htab_insert(parser.glob_tab, NULL, id);
                    pair->param_count = 0;
                    pair->type = H_FUNC_ID;
                    pair->params = NULL;
                    pair->return_type = D_NONE;
                    pair->param_names = NULL;
                }
                data->bucket = pair;
                stack_push(stack, data);
                ID_last_token = true;

            } else if (lookahead->type == T_FLOAT) {

                htab_pair_t *pair = htab_find(parser.temporary_tab, tmp);
                if (pair == NULL) {
                    parser.tmp_counter++;
                    pair = htab_insert(parser.temporary_tab, NULL, tmp);
                    pair->value.number_float = lookahead->value.number_float;
                    pair->value_type = D_FLOAT;
                    pair->type = H_CONSTANT;

                    defvar_order(tmp, pair, gen);

                    operands = malloc(sizeof(htab_pair_t*));
                    operands[0] = pair;
                    generator_add_instruction(gen, gen_instruction_constructor(assign, tmp, operands, NULL, 1, NULL, 0));

                }

                TData *data = stack_data(P_I, P_I);
                data->bucket = pair;

                stack_push(temps, data);
                stack_push(stack, stack_data(P_I, P_I));
            } else if (lookahead->type == T_INT) {

                htab_pair_t *pair = htab_find(parser.temporary_tab, tmp);
                if (pair == NULL) {
                    parser.tmp_counter++;
                    pair = htab_insert(parser.temporary_tab, NULL, tmp);
                    pair->value.number_int = lookahead->value.number_int;
                    pair->value_type = D_INT;
                    pair->type = H_CONSTANT;

                    defvar_order(tmp, pair, gen);

                    operands = malloc(sizeof(htab_pair_t*));
                    operands[0] = pair;
                    generator_add_instruction(gen, gen_instruction_constructor(assign, tmp, operands, NULL, 1, NULL, 0));
                }

                TData *data = stack_data(P_I, P_I);
                data->bucket = pair;

                stack_push(temps, data);
                stack_push(stack, stack_data(P_I, P_I));
            } else if (lookahead->type == T_STRING) {
                htab_pair_t *pair = htab_find(parser.temporary_tab, tmp);
                if (pair == NULL) {
                    parser.tmp_counter++;
                    pair = htab_insert(parser.temporary_tab, NULL, tmp);
                    pair->value.string = lookahead->value.string;
                    pair->value_type = D_STRING;
                    pair->type = H_CONSTANT;

                    defvar_order(tmp, pair, gen);

                    operands = malloc(sizeof(htab_pair_t*));
                    operands[0] = pair;
                    generator_add_instruction(gen, gen_instruction_constructor(assign, tmp, operands, NULL, 1, NULL, 0));
                }

                TData *data = stack_data(P_I, P_I);
                data->bucket = pair;

                stack_push(temps, data);
                stack_push(stack, stack_data(P_I, P_I));
            } else if (lookahead->type == T_VAR) {
                htab_pair_t *pair = htab_find(parser.temporary_tab, lookahead->value.identifier);
                if (pair == NULL) {
                    parser.only_defvar = true;
                    parser.tmp_counter++;
                    pair = htab_insert(parser.temporary_tab, NULL, lookahead->value.identifier);
                    pair->value.string = lookahead->value.identifier;
                    pair->value_type = D_NONE;
                    pair->type = H_VAR;

                    defvar_order(tmp, pair, gen);
                }
                TData *data = stack_data(P_I, P_I);
                data->bucket = pair;

                stack_push(temps, data);
                stack_push(stack, stack_data(P_I, P_I));
            } else if (lookahead->type >= T_LESS && lookahead->type <= T_GREATER_EQUAL) {
                stack_push(stack, stack_data(P_R, P_R));
                if (parser.relation_operator == 0) {
                    parser.relation_operator = lookahead->type;
                } else {
                    exit(BAD_TYPE_COMPATIBILTY);
                }
            }  else if (lookahead->value.keyword = KW_NULL && lookahead->type == T_KEYWORD) {

                htab_pair_t *pair = htab_find(parser.temporary_tab, tmp);
                if (pair == NULL) {
                    parser.tmp_counter++;
                    pair = htab_insert(parser.temporary_tab, NULL, tmp);
                    pair->value.keyword = lookahead->value.keyword;
                    pair->value_type = D_VOID;
                    pair->type = H_CONSTANT;

                    defvar_order(tmp, pair, gen);

                    operands = malloc(sizeof(htab_pair_t*));
                    operands[0] = pair;
                    generator_add_instruction(gen, gen_instruction_constructor(assign, tmp, operands, NULL, 1, NULL, 0));
                }

                TData *data = stack_data(P_I, P_I);
                data->bucket = pair;

                stack_push(temps, data);
                stack_push(stack, stack_data(P_I, P_I));
            } else {
                stack_push(stack, stack_data((int) column, (int) column));
            }
        } else {
            while (reduce(stack, shelf, temps, gen, end) == 1);
            if (reduce(stack, shelf, temps, gen, end) != -1) {
                return 0;
            } else {
                TData *top = stack_top(temps);
                if (parser.if_eval) {
                    generator_add_instruction(gen, gen_instruction_constructor(if_, top->bucket->identifier, NULL, NULL, 0, NULL, 0));
                    parser.if_eval = false;
                }
                
                if (parser.while_eval) {
                    generator_add_instruction(gen, gen_instruction_constructor(while_start, top->bucket->identifier, NULL, NULL, 0, NULL, 0));
                    parser.while_eval = false;
                }

                if (parser.expect_ret && top != NULL) parser.val_returned = top->bucket;
                if (parser.in_assign != NULL && top != NULL) {
                    parser.in_assign->value_type = top->bucket->value_type;

                    htab_pair_t **operands = malloc(sizeof(htab_pair_t*));
                    operands[0] = top->bucket;
                    generator_add_instruction(gen, gen_instruction_constructor(assign, parser.in_assign->identifier, operands, NULL, 1, NULL, 0));
                    parser.in_assign = NULL;
                    parser.only_defvar = false;

                } else if (top == NULL) {
                    parser.empty_expr = true;
                }
                if (parser.only_defvar == true) {
                    exit(BAD_UNDEFINED_VAR);
                }

                return 1;
            }
        }
    }

    exit(BAD_LEXEM);
}

int parse(Generator *gen) {
    TStack *stack = NULL;
    stack = stack_init(stack);
    TStack *prec = NULL;
    prec = stack_init(prec);
    TStack *brackets = NULL;
    brackets = stack_init(brackets);

    /* push initial nonterms to stack */
    stack_push(stack, stack_data(T_EOF, T_TERM));
    stack_push(stack, stack_data(N_PROG, T_NONTERM));
    int E = 0;

    Token *token = malloc(sizeof(Token));
    if (token == NULL)  exit(BAD_INTERNAL);
    parser.tmp_token = malloc(sizeof(Token));
    if (parser.tmp_token == NULL) exit(BAD_INTERNAL);

    bool keep_prev_token = false;
    bool return_back = false;
    get_token(token);
    if (token->type == T_ERROR) exit(BAD_LEXEM);
    if (token->type == T_EOF) exit(BAD_SYNTAX);
    printf("# ");

    while(1) {
        if (stack_isEmpty(stack)) {
            break;
        }
        
        TData *top = stack_pop(stack);
        if (top->type == T_TERM) {
            if (top->value == token->type) { 
                if (token->type == T_LEFT_BRACE) {
                    parser.bracket_counter++;
                }
                else if (token->type == T_RIGHT_BRACE) {
                    parser.bracket_counter--;
                    if (!stack_isEmpty(brackets)) {
                        TData *data = stack_top(brackets);
                        if (data->value == parser.bracket_counter) {
                            stack_pop(brackets);

                            if (data->type == KW_IF) {
                                generator_add_instruction(gen, gen_instruction_constructor(else_end, NULL, NULL, NULL, 0, NULL, 0));
                                parser.while_count -= 1;
                                if (parser.while_count == 0) {
                                    generator_add_instruction(gen, parser.in_while);
                                    parser.in_while = NULL;
                                }
                                
                            }
                            else if (data->type == KW_WHILE) {
                                generator_add_instruction(gen, gen_instruction_constructor(while_end, NULL, NULL, NULL, 0, NULL, 0));
                                parser.while_count -= 1;
                                if (parser.while_count == 0) {
                                    generator_add_instruction(gen, parser.in_while);
                                    parser.in_while = NULL;
                                }
                            }
                            free(data);
                        }
                    }
                    if (parser.bracket_counter == 0 && parser.temporary_tab != parser.glob_tab) {

                        /* missing closing brace */
                        if (stack_isEmpty(parser.local_tabs)) {
                            exit(BAD_SYNTAX); 
                        }
                        /* return from a function */
                        stack_pop(parser.local_tabs);
                        if (stack_isEmpty(parser.local_tabs)) parser.temporary_tab = parser.glob_tab;
                        else parser.temporary_tab = stack_top(parser.local_tabs)->htab;

                        parser.in_function = false;
                        Instruction *instr = gen_instruction_constructor(0, NULL, NULL, NULL, 0, NULL, 0);
                        if (!parser.in_func->strict_return || parser.in_func->return_type == D_VOID) {
                            instr->instruct = end_fn_void;                            
                        }
                        else {
                            instr->instruct = err_quit4;
                        }
                        generator_add_instruction(gen, instr);
                        generator_add_instruction(gen, parser.in_fn);
                        parser.in_func = NULL;
                    }
                }

                /* definition of a function */
                if (parser.in_func != NULL) {
                    if (parser.in_param_def && token->type == T_RIGHT_BRACKET) {
                        parser.in_param_def = false;
                    }
                    else if (!parser.in_param_def && token->type == T_TYPE) {
                        if (parser.in_func->return_type == D_NONE && parser.in_func->param_count != E) exit(BAD_TYPE_OR_RETURN);
                        switch (token->value.keyword) {
                            case KW_INT:
                                parser.in_func->return_type = D_INT;
                                break;
                            case KW_FLOAT:
                                parser.in_func->return_type = D_FLOAT;
                                break;
                            case KW_STRING:
                                parser.in_func->return_type = D_STRING;
                                break;
                            case KW_VOID:
                                parser.in_func->return_type = D_VOID;
                                break;
                            default:
                                exit(BAD_SYNTAX); // unknown data type
                        }
                        E = 0;
                       // parser.val_expected = parser.in_func->return_type;
                        parser.val_returned = NULL;
                        parser.in_func->strict_return = token->strict_type;
                    }
                    else if (parser.in_param_def && token->type == T_TYPE) {
                        DataType type;
                        switch (token->value.keyword) {
                            case KW_INT:
                                type = D_INT;
                                break;
                            case KW_FLOAT:
                                type = D_FLOAT;
                                break;
                            case KW_STRING:
                                type = D_STRING;
                                break;
                            default:
                                exit(BAD_SYNTAX); // unknown data type
                        }
                        if (parser.in_func->return_type != D_NONE) {
                            parser.in_func->param_count += 1;
                        
                            parser.in_func->params = realloc(parser.in_func->params, sizeof(Value) * parser.in_func->param_count);
                            if (parser.in_func->params == NULL) exit(BAD_INTERNAL); // realloc failed

                            parser.in_func->params[parser.in_func->param_count - 1] = type;

                            parser.in_func->params_strict = realloc(parser.in_func->params_strict, sizeof(bool) * parser.in_func->param_count);
                            if (parser.in_func->params_strict == NULL) exit(BAD_INTERNAL); // realloc failed
                            parser.in_func->params_strict[parser.in_func->param_count - 1] = token->strict_type;
                        }
                        else {
                            if (E >= parser.in_func->param_count || 
                                parser.in_func->params[E] != type ||
                                parser.in_func->params[E] == D_NONE && token->strict_type) 
                                    exit(BAD_TYPE_OR_RETURN);
                            //if (parser.in_func->params[E++] != type) exit (BAD_TYPE_OR_RETURN);
                        }
                        
                    }
                    else if (parser.in_param_def && token->type == T_VAR) {
                        htab_pair_t *frame_item = htab_find(parser.temporary_tab, token->value.identifier);
                        /* add the var to the table */
                        if (frame_item != NULL) {
                            exit(BAD_DEFINITION); // two parameters with the same name
                        }
                        else {
                            int idx = E - 1;
                            if (parser.in_func->return_type != D_NONE) {
                                idx = parser.in_func->param_count - 1;
                            }
                            frame_item = htab_insert(parser.temporary_tab, token, token->value.identifier);
                            frame_item->value_type = parser.in_func->params[idx];

                            parser.in_func->param_names = realloc(parser.in_func->param_names, sizeof(char *) * (idx + 1));
                            parser.in_func->param_names[idx] = malloc(sizeof(char) * strlen(token->value.identifier));
                            strcpy(parser.in_func->param_names[idx], token->value.identifier);
                        }
                    }
                }
                
                get_next_token(&token, &keep_prev_token, &return_back);

                if (token->type == T_ASSIGN && parser.tmp_token->type == T_VAR) {
                    parser.in_assign = htab_find(parser.temporary_tab, parser.tmp_token->value.identifier);
                    /* add the var if it's not currently in the table */
                    if (parser.in_assign == NULL) {
                        parser.in_assign = htab_insert(parser.temporary_tab, parser.tmp_token, parser.tmp_token->value.identifier);
                        parser.in_assign->value_type = D_NONE;

                        defvar_order(parser.tmp_token->value.identifier, parser.in_assign, gen);
                        parser.only_defvar = true;
                    }
                }
            }
            else {
                fprintf(stderr, "terms not matching\n");
                exit(BAD_SYNTAX);
            }
        }
        else if (top->type == T_KW) {
            if (token->type == T_KEYWORD && top->value == token->value.keyword) {
                if (token->value.keyword == KW_IF) {
                    parser.if_eval = true;
                    parser.while_count += 1;


                    generator_add_instruction(gen, gen_instruction_constructor(if_start, NULL, NULL, NULL, 0, NULL, parser.in_while == NULL));


                    if (parser.in_while == NULL) {
                        Instruction *instr = gen_instruction_constructor(while_defs, NULL, NULL, NULL, 0, NULL, parser.in_while == NULL);
                        parser.in_while = instr;
                    }

                }
                if (token->value.keyword == KW_WHILE) {
                    parser.while_eval = true;
                    parser.while_count += 1;

                    generator_add_instruction(gen, gen_instruction_constructor(while_, NULL, NULL, NULL, 0, NULL, parser.in_while == NULL));

                    TData *data = malloc(sizeof(TData));
                    data->value = parser.bracket_counter;
                    data->type = KW_WHILE;
                    stack_push(brackets, data);

                    if (parser.in_while == NULL) {
                        Instruction *instr = gen_instruction_constructor(while_defs, NULL, NULL, NULL, 0, NULL, 0);
                        parser.in_while = instr;
                    }
                }

                if (token->value.keyword == KW_ELSE) {
                    generator_add_instruction(gen, gen_instruction_constructor(else_, NULL, NULL, NULL, 0, NULL, 0));


                    TData *data = malloc(sizeof(TData));
                    data->value = parser.bracket_counter;
                    data->type = KW_IF;
                    stack_push(brackets, data);
                }

                if (token->value.keyword == KW_RETURN){
                    parser.expect_ret = true;
                    parser.allow_expr_empty = false;
                    if (parser.temporary_tab == parser.glob_tab || (parser.in_func->return_type == D_VOID)) {
                        parser.allow_expr_empty = true;
                    }
                }

                get_next_token(&token, &keep_prev_token, &return_back);

                /* function definition - create new item in tab */
                if (parser.tmp_token->value.keyword == KW_FUNCTION && token->type == T_IDENTIFIER) { 
                    parser.in_function = true;
                    parser.bracket_counter = 0;
                    char *id = malloc(strlen(token->value.identifier) + 5);
                    strcpy(id, "69");
                    strcat(id, token->value.identifier);

                    /* check if the function is not already defined */
                    parser.in_func = htab_find(parser.temporary_tab, id);
                    /* redefinition of function -> exit */
                    if (parser.in_func != NULL && parser.in_func->return_type != D_NONE) {
                        exit(BAD_DEFINITION);
                    }
                    else if (parser.in_func == NULL){  
                        /* else insert to tab */
                        parser.in_func = htab_insert(parser.temporary_tab, token, id);
                    }
                    parser.in_func->param_count = 0;
                    parser.in_func->params = NULL;
                    parser.in_func->return_type = D_UNDEF;
                    parser.in_func->param_names = NULL;
                    parser.in_param_def = true;

                    /* create new frame for current function call */
                    htab_t *new_tab = htab_init(LOCALTAB_SIZE);
                    TData *new_data = malloc(sizeof(TData));
                    new_data->bucket = NULL;
                    new_data->htab = new_tab;
                    stack_push(parser.local_tabs, new_data);
                    parser.temporary_tab = new_tab;

                    /* create label and pushframe */
                    htab_pair_t **operands = malloc(sizeof(htab_pair_t *));
                    operands[0] = parser.in_func;
                    generator_add_instruction(gen, gen_instruction_constructor(start_fn, NULL, operands, NULL, 1, NULL, 0));


                    Instruction *temp = gen_instruction_constructor(fn_defs, NULL, NULL, NULL, 0, NULL, 0);
                    parser.in_fn = temp;
                }  
            }
            else {
                /* terms not matching */
                exit(BAD_SYNTAX);
            }

        }
        else if (top->type == T_NONTERM) {
            if (top->value == N_SMALL_ST && token->type != T_ASSIGN) {
                return_back = true;
            }
            if (top->value == N_EXPR) {

                /* CALL PRECEDENTIAL */
                keep_prev_token = true;
                
                int result = precedence(prec, &token, &keep_prev_token, &return_back, gen);
                stack_dispose(prec);
                
                if (!result) {
                    exit(BAD_UNDEFINED_VAR);
                }

                else if (parser.empty_expr && !parser.allow_expr_empty) {
                    exit(BAD_TERM);
                }
                parser.in_assign = NULL;
                get_next_token(&token, &keep_prev_token, &return_back);

                if (parser.expect_ret) {
                    if (parser.glob_tab == parser.temporary_tab) {
                        generator_add_instruction(gen, gen_instruction_constructor(exit_success, NULL, NULL, NULL, 0, NULL, 0));
                    }
                    else {                             
                        if (!parser.empty_expr) {

                            Instruction *instr = gen_instruction_constructor(0, NULL, NULL, NULL, 0, NULL, 0);
                            instr->operands = malloc(sizeof(htab_pair_t *));
                            instr->operands[0] = parser.val_returned;

                            switch (parser.in_func->return_type) {
                                case D_INT:
                                    instr->instruct = end_fn_int;
                                    break;
                                case D_FLOAT:
                                    instr->instruct = end_fn_float;
                                    break;
                                case D_STRING:
                                    instr->instruct = end_fn_string;
                                    break;
                                case D_VOID:
                                    instr->instruct = end_fn_void;
                                    break;
                            }
                            generator_add_instruction(gen, instr);
                        } 
                        else {
                            generator_add_instruction(gen, gen_instruction_constructor(end_fn_void, NULL, NULL, NULL, 0, NULL, 0));
                        }
                    }
                    
                }
                
                parser.expect_ret = false;
                parser.allow_expr_empty = false;
                continue;
            }

            unsigned int col_idx, row_idx;
            if (token->type == T_KEYWORD) {
                col_idx = token->value.keyword;
            }
            else col_idx = token->type;

            row_idx = top->value;

            unsigned int val = LL_TABLE[row_idx][col_idx];
            if (val == 0) val = LL_TABLE[row_idx][EPS];

            printf("%d ", val);

            apply_rule(stack, val);
        }
        else {
            /* terms not matching */
            exit(BAD_SYNTAX);
        }
    }
    printf("\n");
    generator_add_instruction(gen, gen_instruction_constructor(end, NULL, NULL, NULL, 0, NULL, 0));
    stack_dispose(stack);
    //stack_dispose(parser.local_tabs);
    //htab_free(parser.glob_tab);
    return 0;
}

void insert_builtins(void) {
    char *identifier = malloc(sizeof(char)*10);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcpy(identifier, "69reads");
    parser.builtins[0] = identifier;
    htab_pair_t *reads = htab_insert(parser.glob_tab, NULL, identifier);
    if (reads == NULL) exit(BAD_INTERNAL);
    reads->type = H_FUNC_ID;
    reads->param_count = 0;
    reads->return_type = D_STRING;

    identifier = malloc(sizeof(char)*10);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcpy(identifier, "69readi");
    parser.builtins[1] = identifier;
    htab_pair_t *readi = htab_insert(parser.glob_tab, NULL, identifier);
    if (readi == NULL) exit(BAD_INTERNAL);
    readi->type = H_FUNC_ID;
    readi->param_count = 0;
    readi->return_type = D_INT;

    identifier = malloc(sizeof(char)*10);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcpy(identifier, "69readf");
    parser.builtins[2] = identifier;
    htab_pair_t *readf = htab_insert(parser.glob_tab, NULL, identifier);
    if (readf == NULL) exit(BAD_INTERNAL);
    readf->type = H_FUNC_ID;
    readf->param_count = 0;
    readf->return_type = D_FLOAT;

    identifier = malloc(sizeof(char)*10);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcpy(identifier, "69strlen");
    parser.builtins[3] = identifier;
    htab_pair_t *strlen_ = htab_insert(parser.glob_tab, NULL, identifier);
    if (strlen_ == NULL) exit(BAD_INTERNAL);
    strlen_->type = H_FUNC_ID;
    strlen_->params = malloc(sizeof(DataType));
    if (strlen_->params == NULL) exit(BAD_INTERNAL);
    strlen_->params[0] = D_STRING;
    strlen_->param_count = 1;
    strlen_->return_type = D_INT;

    identifier = malloc(sizeof(char)*15);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcpy(identifier, "69substring");
    parser.builtins[4] = identifier;
    htab_pair_t *substring = htab_insert(parser.glob_tab, NULL, identifier);
    if (substring == NULL) exit(BAD_INTERNAL);
    substring->type = H_FUNC_ID;
    substring->params = malloc(sizeof(DataType)*3);
    if (substring->params == NULL) exit(BAD_INTERNAL);
    substring->params[0] = D_STRING;
    substring->params[1] = D_INT;
    substring->params[2] = D_INT;
    substring->param_count = 3;
    substring->return_type = D_STRING;

    identifier = calloc(sizeof(char)*10, 10);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcat(identifier, "69ord");
    parser.builtins[5] = identifier;
    htab_pair_t *ord_ = htab_insert(parser.glob_tab, NULL, identifier);
    if (ord_ == NULL) exit(BAD_INTERNAL);
    ord_->type = H_FUNC_ID;
    ord_->params = malloc(sizeof(DataType));
    if (ord_->params == NULL) exit(BAD_INTERNAL);
    ord_->params[0] = D_STRING;
    ord_->param_count = 1;
    ord_->return_type = D_INT;

    identifier = calloc(sizeof(char)*10, 10);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcat(identifier, "69chr");
    parser.builtins[6] = identifier;
    htab_pair_t *chr_ = htab_insert(parser.glob_tab, NULL, identifier);
    if (chr_ == NULL) exit(BAD_INTERNAL);
    chr_->type = H_FUNC_ID;
    chr_->params = malloc(sizeof(DataType));
    if (chr_->params == NULL) exit(BAD_INTERNAL);
    chr_->params[0] = D_INT;
    chr_->param_count = 1;
    chr_->return_type = D_STRING;

    identifier = calloc(sizeof(char)*20, 20);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcat(identifier, "69strval");
    parser.builtins[7] = identifier;
    htab_pair_t *strval_i = htab_insert(parser.glob_tab, NULL, identifier);
    if (strval_i == NULL) exit(BAD_INTERNAL);
    strval_i->type = H_FUNC_ID;
    strval_i->params = malloc(sizeof(DataType));
    if (strval_i->params == NULL) exit(BAD_INTERNAL);
    strval_i->params[0] = D_STRING;
    strval_i->param_count = 1;
    strval_i->return_type = D_STRING;

    identifier = calloc(sizeof(char)*20, 20);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcat(identifier, "69floatval");
    parser.builtins[8] = identifier;
    htab_pair_t *floatval_i = htab_insert(parser.glob_tab, NULL, identifier);
    if (floatval_i == NULL) exit(BAD_INTERNAL);
    floatval_i->type = H_FUNC_ID;
    floatval_i->params = malloc(sizeof(DataType));
    if (floatval_i->params == NULL) exit(BAD_INTERNAL);
    floatval_i->params[0] = D_FLOAT;
    floatval_i->param_count = 1;
    floatval_i->return_type = D_FLOAT;

    identifier = calloc(sizeof(char)*20, 20);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcat(identifier, "69intval");
    parser.builtins[9] = identifier;
    htab_pair_t *intval_i = htab_insert(parser.glob_tab, NULL, identifier);
    if (intval_i == NULL) exit(BAD_INTERNAL);
    intval_i->type = H_FUNC_ID;
    intval_i->params = malloc(sizeof(DataType));
    if (intval_i->params == NULL) exit(BAD_INTERNAL);
    intval_i->params[0] = D_INT;
    intval_i->param_count = 1;
    intval_i->return_type = D_INT;

    identifier = calloc(sizeof(char)*20, 20);
    if (identifier == NULL) exit(BAD_INTERNAL);
    strcat(identifier, "69write");
    parser.builtins[10] = identifier;
    htab_pair_t *write = htab_insert(parser.glob_tab, NULL, identifier);
    if (write == NULL) exit(BAD_INTERNAL);
    write->type = H_FUNC_ID;
    write->param_count = -1;
    write->return_type = D_VOID;

}

int main(void) {
    stream = stdin;
    //stream = fopen("test.php", "r");
    if (stream == NULL) exit(BAD_INTERNAL);

    Generator *gen = malloc(sizeof(Generator));
    generator_init(gen);

    /* initialize the parser struct */
    parser.builtins = malloc(sizeof(char *) * 11);
    parser.tmp_token = NULL;
    parser.glob_tab = htab_init(GLOBTAB_SIZE);
    parser.temporary_tab = parser.glob_tab;
    parser.local_tabs = stack_init(parser.local_tabs);
    parser.in_func = NULL;
    parser.in_assign = NULL;
    parser.in_param_def = false;
    parser.empty_expr = false;
    parser.allow_expr_empty = false;
    parser.tmp_counter = 0;
    parser.relation_operator = 0;
    parser.expect_ret = false;
    parser.bracket_counter = 0;
    parser.val_returned = NULL;
    //parser.val_expected = D_VOID;
    parser.if_eval = false;
    parser.while_eval = false;
    parser.in_function = false;
    parser.in_while = NULL;
    parser.in_fn = NULL;
    parser.while_count = 0;
    parser.only_defvar = false;

    insert_builtins();

    int result = parse(gen);
    if (result) {
        return result;
    }

    generate(gen);
    // free parser struct
    //free(parser.builtins);

    return 0;
}
