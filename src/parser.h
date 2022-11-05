

const unsigned int LL_TABLE[8][15] = { {1},
                                        {0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 4},
                                        {0, 8, 11, 12, 10, 5, 6, 9},
                                        {[9] = 13, 14},
                                        {[8] = 16},
                                        {[7] = 17},
                                        {[11] = 19, [14] = 18},
                                        {0, 20, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0, 0, 21} };

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

const unsigned int PREC_TABLE[14][14] = { //TODO
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
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN, [8] = P_OPEN, [12] = P_OPEN},
        {[6] = P_EQUAL},
        {P_OPEN, P_OPEN, P_OPEN, P_OPEN, P_OPEN,P_OPEN, P_OPEN, P_EQUAL, P_OPEN, [12] = P_OPEN, P_EQUAL}
};



typedef enum {
    N_PROG,
    N_ST_LIST,
    N_ST,
    N_SMALL_ST,
    N_PARAM_DEF,
    N_PARAM_NAME,
    N_PARAM_LIST,
    N_BODY,
    N_EPS,
    N_EXPR
} NonTerm;

typedef enum {
    T_TERM,
    T_NONTERM,
    T_KW
} TermType;

//extern Token *tmp_token;

//Token *tmp_token = NULL;