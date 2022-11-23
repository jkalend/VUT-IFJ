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
    ret,
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
    main_,
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
    fn_defs
}InstructionType;

typedef struct Instruction {
    InstructionType instruct;
    const char *id; // for call and defvar
    htab_pair_t **operands; // for call op0 will be the label
    DataType *types;
    int operands_count;
    htab_pair_t **params;
    int params_count;
    DataType retval;
} Instruction;

typedef struct {
    // these 3 might not be needed at all
    // started var signalises that the generator has started and printed the ifjcode22 header
    bool in_function;
    bool in_while;
    bool started;
    int label_count;


    Instruction **instructions;
    long instruction_count;
    int fn_temps;
    TStack *label_stack;

} Generator;

void generator_init(Generator *);

int generate(Generator *);

void generator_add_instruction(Generator *, Instruction *);

void generator_free(Generator *);

Instruction *generate_instruction(InstructionType instruct,
                                  char *id,
                                  char **operands,
                                  int *types,
                                  int operands_count,
                                  char **params,
                                  int params_count,
                                  DataType retval);

#endif //IFJ_GENERATOR_H
