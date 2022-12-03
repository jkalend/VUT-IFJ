//
// Created by Kalenda, Jan on 18.11.2022.
//

#ifndef IFJ_GENERATOR_H
#define IFJ_GENERATOR_H

#include "error.h"
#include "stack.h"
#include "symtable.h"
#include "scanner.h"
#include "parser.h"

typedef enum {
    reads,
    readi,
    readf,
    strlen_,
    substring,
    ord,
    chr,
    strval,
    floatval,
    intval,
    write,
    // do NOT move anything above this comment
    concat,
    assign,
    defvar,
    call,
    addition,
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
    end,
    start_fn,
    end_fn_string,
    end_fn_float,
    end_fn_int,
    end_fn_void,
    while_,
    while_start,
    while_end,
    if_,
    else_,
    else_end,
    while_defs,
    err_quit4,
    err_quit6,
    fn_defs,
    exit_success,
    if_start
}InstructionType;

typedef struct Instruction {
    int operands_count;
    int params_count;
    InstructionType instruct;
    char *id; // for call and defvar
    htab_pair_t **operands; // for call op0 will be the label
    DataType *types;
    htab_pair_t **params;
} Instruction;

typedef struct Generator {
    int label_count;
    Instruction **instructions;
    long instruction_count;
    TStack *label_stack;
} Generator;

void generator_init(Generator *);

void generate(Generator *, struct parser_t *);

void generator_add_instruction(Generator *, Instruction *);

void generator_free(Generator *);

Instruction *gen_instruction_constructor(InstructionType instruct,
                                         char *id,
                                         htab_pair_t **operands,
                                         DataType *types,
                                         int operands_count,
                                         htab_pair_t **params,
                                         int params_count);


#endif //IFJ_GENERATOR_H
