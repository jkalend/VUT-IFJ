//
// Created by Kalenda, Jan on 18.11.2022.
//

#include "generator.h"
#include <stdio.h>


void generator_init(Generator *generator) {
    generator->in_function = false;
    generator->in_while = false;
    generator->instructions = malloc(sizeof(Instruction *) * 200);
    if (generator->instructions == NULL) {
        exit(BAD_INTERNAL);
    }
    generator->instruction_count = 0;
}

void generator_free(Generator *generator) {
    for (int i = 0; i < generator->instruction_count; i++) {
        free(generator->instructions[i]->id);
        for (int j = 0; j < generator->instructions[i]->operands_count; j++) {
            free(generator->instructions[i]->operands[j]);
        }
        free(generator->instructions[i]->operands);
        for (int j = 0; j < generator->instructions[i]->params_count; j++) {
            free(generator->instructions[i]->params[j]);
        }
        free(generator->instructions[i]->params);
    }
    free(generator->instructions);
}

void generator_add_instruction(Generator *generator, Instruction *instruction) {
    if (generator->instruction_count % 100 == 0) {
        generator->instructions = realloc(generator->instructions, sizeof(Instruction*) * (generator->instruction_count + 200));
        if (generator->instructions == NULL) {
            exit(BAD_INTERNAL);
        }
    }
    generator->instructions[generator->instruction_count] = instruction;
    generator->instruction_count++;
}

int generate(const Generator *generator) {
    printf(".IFJcode22\n");
    printf("defvar GF@%%bool\n");
    printf("defvar GF@%%int\n");
    printf("defvar GF@%%float\n");
    printf("defvar GF@%%string\n");
    printf("defvar GF@%%nil\n");
    printf("move GF@%%bool string@bool\n");
    printf("move GF@%%int string@int\n");
    printf("move GF@%%float string@float\n");
    printf("move GF@%%string string@string\n");
    printf("move GF@%%nil string@nil\n");
    printf("jump $$main\n");

    for (long i = 0; i < generator->instruction_count; i++) {
        //individual instruction generation
        //each instruction has its own function
        switch (generator->instructions[i]->instruct) {
            case assign:
                break;
            case defvar:
                break;
            case call:
                break;
            case ret:
                break;
            case add:
                break;
            case sub:
                break;
            case mul:
                break;
            case div_:
                break;
            case idiv:
                break;
            case lt:
                break;
            case gt:
                break;
            case eq:
                break;
            case lte:
                break;
            case gte:
                break;
            case neq:
                break;
            case floatval:
                break;
            case intval:
                break;
            case strval:
                break;
            case substring:
                break;
            case ord:
                break;
            case chr:
                break;
            case reads:
                break;
            case readf:
                break;
            case readi:
                break;
            case write:
                break;
            case concat:
                break;
            case strlen_:
                break;
            case main_:
                printf("LABEL $$main\n");
                printf("CREATEFRAME\n");
                printf("PUSHFRAME\n");
                break;
            case end:
                printf("EXIT int@0\n");
                break;
            default:
                break;
        }
    }

    return  0;
}
