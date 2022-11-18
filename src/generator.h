//
// Created by Kalenda, Jan on 18.11.2022.
//

#ifndef IFJ_GENERATOR_H
#define IFJ_GENERATOR_H

#include "error.h"
#include "stack.h"
#include "htab.h"
#include "scanner.h"
#include "parser.h"

typedef enum {
    assign,
    defvar,
    call,
    ret,
    add,
    sub,
    mul,
    div_,
    idiv,
    lt,
    gt,
    eq,
    lte,
    gte,
    neq,
    floatval,
    intval,
    strval,
    substring,
    ord,
    chr,
    reads,
    readf,
    readi,
    write,
    concat,
    strlen_,
    main_,
    end
}InstructionType;

typedef struct {
    InstructionType instruct;
    char *id; // function id, variable id
    char **operands;
    int *types; // 0 - int, 1 - float, 2 - string, 3 - bool, 4 - nil, 5 - var, 6 - function
    int operands_count;
    char **params;
    int params_count;
    DataType retval;
}Instruction;

typedef struct {
    // these 3 might not be needed at all
    // started var signalises that the generator has started and printed the ifjcode22 header
    bool in_function;
    bool in_while;
    // bool started;


    Instruction **instructions;
    long instruction_count;

}Generator;

void generator_init(Generator *);

int generate(const Generator *);

void generator_add_instruction(Generator *, Instruction *);

void generator_free(Generator *);

#endif //IFJ_GENERATOR_H
