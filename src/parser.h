#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "htab.h"

const unsigned int LL_TABLE[8][33] = {{1},
                                      {0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 4, [15] =  2, 2, 2, 2},
                                      {0, 7, 11, 12, 10, 5, 6, 9, 0, 7, [15] =  7, 7, 7, 7},
                                      {[9] = 13, 14, [19] = 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15},
                                      {[8] = 16, [14] = 22},
                                      {[7] = 17},
                                      {[11] = 19, [14] = 18},
                                      {0, 20, 20, 20, 20, 0, 20, 20, 0, 0, 0, 0, 0, 0, 21} };

extern const unsigned int PREC_TABLE[14][14];
extern Token *tmp_token;

#define EPS 14 // eps has column index 14 in ll table
#define GLOBTAB_SIZE 2003 // num of buckets to allocate for global symtab
#define LOCALTAB_SIZE 557 // num of buckets to allocate for local symtabs

typedef enum {
    N_PROG,
    N_ST_LIST,
    N_ST,
    N_SMALL_ST,
    N_PARAM_DEF,
    N_PARAM_NAME,
    N_PARAM_LIST,
    N_BODY,
    N_EXPR
} NonTerm;

typedef enum {
    T_TERM,
    T_NONTERM,
    T_KW,
    T_TOKEN
} TermType;

typedef enum {
    P_MUL,
    P_DIV,
    P_ADD,
    P_SUB,
    P_CONC,
    P_I,
    P_LEFT_BRACKET,
    P_RIGHT_BRACKET,
    P_R,
    P_TYPE_EQ,
    P_TYPE_NEQ,
    P_END,
    P_FN,
    P_COMMA,
    P_OPEN,
    P_CLOSE,
    P_EQUAL,
    P_E
}PrecSyms;
#endif // PARSER_H
