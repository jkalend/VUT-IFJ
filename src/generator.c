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
    generator->fn_temps = 0;
}

void gen_strlen(Instruction *instruction, Generator *generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
    printf("MOVE LF@%s string@\n", instruction->params[0]->identifier);

    printf("LABEL !!%d\n", generator->label_count);
    generator->label_count++;
    printf("STRLEN LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);
}

void gen_substring(Instruction *instruction, Generator *generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
}

void gen_ord(Instruction *instruction, Generator *generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
	printf("MOVE LF@%s int@0\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 1);

	printf("LABEL !!%d\n", generator->label_count);
	printf("STRI2INT LF@%s LF@%s int@0\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 1);
	generator->label_count += 2;
}

void gen_chr(Instruction *instruction, Generator *generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 1);
	printf("INT2CHAR LF@%s int@0\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 2);

	printf("LABEL !!%d\n", generator->label_count + 1);
	printf("FLOAT2INT LF@%s LF@%s\n", instruction->params[0]->identifier, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count);
	printf("INT2CHAR LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 2);
	generator->label_count += 3;
}

void gen_write(Instruction *instruction) {
    for (int i = 0; i < instruction->params_count; i++) {
        printf("WRITE LF@%s\n", instruction->params[i]->identifier);
    }
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
            //printf("DPRINT LF@%s\n", instruction->id);
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

void gen_sub(Instruction *instruction, Generator *generator) {
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
    printf("SUB LF@%s LF@%s LF@%s\n",
           instruction->id,
           instruction->operands[0]->identifier,
           instruction->operands[1]->identifier
    );
}

void gen_mul(Instruction *instruction, Generator *generator) {
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
    printf("MUL LF@%s LF@%s LF@%s\n",
           instruction->id,
           instruction->operands[0]->identifier,
           instruction->operands[1]->identifier
    );
}

void gen_div(Instruction *instruction, Generator *generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 2);
    printf("MOVE LF@%s float@%a\n", instruction->operands[0]->identifier, 0.0);
    printf("JUMP !!%d\n", generator->label_count);

    printf("LABEL !!%d\n", generator->label_count); //if op1 float
    generator->label_count++;
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 2); //both floats done here
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
    printf("MOVE LF@%s float@%a\n", instruction->operands[1]->identifier, 0.0);
    printf("JUMP !!%d\n", generator->label_count + 2);


    printf("LABEL !!%d\n", generator->label_count); //if op1 float op2 int
    generator->label_count++;
    printf("INT2FLOAT LF@%s LF@%s\n", instruction->operands[1]->identifier, instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count + 1);


    printf("LABEL !!%d\n", generator->label_count); //if op1 int
    generator->label_count++;
    printf("INT2FLOAT LF@%s LF@%s\n", instruction->operands[0]->identifier, instruction->operands[0]->identifier);
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count - 2); // convert to float
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("MOVE LF@%s float@%a\n", instruction->operands[1]->identifier, 0.0);
    printf("JUMP !!%d\n", generator->label_count);

    printf("LABEL !!%d\n", generator->label_count); //both floats or ints
    generator->label_count++;
    printf("DIV LF@%s LF@%s LF@%s\n",
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

void gen_call(Instruction *instruction) {
    printf("CREATEFRAME\n");
    for (int i = 0; i < instruction->params_count; i++) {
        printf("DEFVAR TF@%s\n", instruction->operands[0]->param_names[i]);
        printf("MOVE TF@%s LF@%s\n", instruction->operands[0]->param_names[i], instruction->params[i]->identifier);
    }
    printf("CALL $!%s\n", instruction->operands[0]->identifier);
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
                gen_call(generator->instructions[i]);
                break;
            case ret:
                break;
            case addition:
                gen_add(generator->instructions[i], generator);
                break;
            case sub:
                gen_sub(generator->instructions[i], generator);
                break;
            case mul:
                gen_mul(generator->instructions[i], generator);
                break;
            case div_:
                gen_div(generator->instructions[i], generator);
                break;
            case idiv: //never happens
                gen_div(generator->instructions[i], generator);
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
				gen_ord(generator->instructions[i], generator);
                break;
            case chr:
				gen_chr(generator->instructions[i], generator);
                break;
            case reads:
				printf("READ LF@%s string\n", generator->instructions[i]->id);
                break;
            case readf:
				printf("READ LF@%s float\n", generator->instructions[i]->id);
                break;
            case readi:
				printf("READ LF@%s int\n", generator->instructions[i]->id);
                break;
            case write:
                gen_write(generator->instructions[i]);
                break;
            case concat:
                gen_concat(generator->instructions[i], generator);
                break;
            case strlen_:
                gen_strlen(generator->instructions[i], generator);
                break;
            case main_:
                printf("LABEL $$main\n");
                printf("CREATEFRAME\n");
                printf("PUSHFRAME\n");
                break;
            case end:
                printf("EXIT int@0\n");
                break;
            case start_fn:    
                printf("LABEL $%s\n", generator->instructions[i]->operands[0]->identifier);
                printf("PUSHFRAME\n");
                printf("DEFVAR LF@$$retval\n");
                printf("MOVE LF@$$retval nil@nil\n");
                break;
            case end_fn:
                if (generator->instructions[i]->operands != NULL) 
                    printf("MOVE LF@$$retval LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                printf("POPFRAME\n");
                printf("RET\n");
            default:
                break;
        }
    }

    return  0;
}
