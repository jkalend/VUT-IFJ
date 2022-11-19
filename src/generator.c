//
// Created by Kalenda, Jan on 18.11.2022.
//

#include "generator.h"
#include <stdio.h>
#include <math.h>


void generator_init(Generator *generator) {
    generator->in_function = false;
    generator->in_while = false;
    generator->started = false;
    generator->label_count = 0;
    generator->instructions = malloc(sizeof(Instruction *) * 200);
    if (generator->instructions == NULL) {
        exit(BAD_INTERNAL);
    }
    generator->instruction_count = 0;
}

void gen_strlen(Instruction *instruction) {
    // not happening here likely
    if (instruction->operands_count != 1) {
        exit(BAD_INTERNAL);
    }
    if (instruction->operands[0]->value_type != D_STRING) {
        exit(BAD_TYPE_COMPATIBILTY);
    }
    //FIXME missing null
    printf("STRLEN LF@%s LF@%s", instruction->id, instruction->operands[0]->value.string);
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
        generator->instructions = realloc(
                generator->instructions, sizeof(Instruction*) * (generator->instruction_count + 200));
        if (generator->instructions == NULL) {
            exit(BAD_INTERNAL);
        }
    }
    generator->instructions[generator->instruction_count] = instruction;
    generator->instruction_count++;
}

void gen_assign(Instruction *instruction) {
    switch (instruction->operands[0]->type) {
        case H_CONSTANT:
            switch (instruction->operands[0]->value_type) {
                case D_INT:
                    printf("MOVE LF@%s int@%lld\n",
                           instruction->id, instruction->operands[0]->value.number_int);
                    break;
                case D_FLOAT:
                    printf("MOVE LF@%s float@%a\n",
                           instruction->id, instruction->operands[0]->value.number_float);
                    break;
                case D_STRING:
                    printf("MOVE LF@%s string@%s\n",
                           instruction->id, instruction->operands[0]->value.string);
                    break;
                case D_VOID:
                    printf("MOVE LF@%s nil@nil\n", instruction->id);
                    break;
                default:
                    break; // FIXME placeholder
            }
            break;
        case H_VAR:
            printf("MOVE LF@%s LF@%s\n", instruction->id, instruction->operands[0]->identifier);
            printf("DPRINT LF@%s\n", instruction->id);
            break;
        default:
            break; // FIXME placeholder
    }
}

void gen_add(Instruction *instruction, Generator *generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 2);
    printf("MOVE LF@%s int@0\n", instruction->operands[0]->identifier);
    printf("JUMP !!%d\n", generator->label_count + 2);

    printf("LABEL !!%d\n", generator->label_count); //if op1 float
    generator->label_count++;
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 3); //both floats done here
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
    printf("MOVE LF@%s float@%a\n", instruction->operands[1]->identifier, 0.0);
    printf("JUMP !!%d\n", generator->label_count + 3);


    printf("LABEL !!%d\n", generator->label_count); //if op1 float op2 int
    generator->label_count++;
    printf("INT2FLOAT LF@%s LF@%s\n", instruction->operands[1]->identifier, instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count + 2);


    printf("LABEL !!%d\n", generator->label_count); //if op1 int or null
    generator->label_count++;
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 1); //both ints done here
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("MOVE LF@%s int@0\n", instruction->operands[1]->identifier); // if null
    printf("JUMP !!%d\n", generator->label_count + 1);

    printf("LABEL !!%d\n", generator->label_count); // op1 int op2 float
    generator->label_count++;
    printf("INT2FLOAT LF@%s LF@%s\n", instruction->operands[0]->identifier, instruction->operands[0]->identifier);

    printf("LABEL !!%d\n", generator->label_count); //both floats or ints
    generator->label_count++;
    printf("ADD LF@%s LF@%s LF@%s\n",
           instruction->id,
           instruction->operands[0]->identifier,
           instruction->operands[1]->identifier
    );
}

void gen_concat(Instruction *instruction, Generator *generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
    printf("MOVE LF@%s string@\n", instruction->operands[0]->identifier);



    printf("LABEL !!%d\n", generator->label_count);
    generator->label_count++;

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
    printf("MOVE LF@%s string@\n", instruction->operands[1]->identifier);

    printf("LABEL !!%d\n", generator->label_count);
    generator->label_count++;
    printf("CONCAT LF@%s LF@%s LF@%s\n",
           instruction->id,
           instruction->operands[0]->identifier,
           instruction->operands[1]->identifier
    );
}

int generate(Generator *generator) {
    printf(".IFJcode22\n");
    printf("defvar GF@%%bool\n");
    printf("defvar GF@%%int\n");
    printf("defvar GF@%%float\n");
    printf("defvar GF@%%string\n");
    printf("defvar GF@%%nil\n");
    printf("defvar GF@%%check0\n");
    printf("defvar GF@%%check1\n");
    printf("defvar GF@%%check2\n");
    printf("defvar GF@%%index\n");
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
                gen_assign(generator->instructions[i]);
                break;
            case defvar:
                printf("defvar LF@%s\n", generator->instructions[i]->id);
                break;
            case call:
                break;
            case ret:
                break;
            case addition:
                gen_add(generator->instructions[i], generator);
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
                gen_concat(generator->instructions[i], generator);
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
