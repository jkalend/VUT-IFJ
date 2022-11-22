//
// Created by Kalenda, Jan on 18.11.2022.
//

#include "generator.h"
#include <stdio.h>


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
    generator->label_stack = stack_init(generator->label_stack);
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
	printf("JUMP !!%d\n", generator->label_count + 4);

	printf("LABEL !!%d\n", generator->label_count);
	//string checked
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[1]->identifier);
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 1);
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[1]->identifier);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 2);
	printf("MOVE LF@%s int@0\n", instruction->params[1]->identifier);
	printf("JUMP !!%d\n", generator->label_count + 1);

	printf("LABEL !!%d\n", generator->label_count + 2);
	printf("FLOAT2INT LF@%s LF@%s\n", instruction->params[1]->identifier, instruction->params[1]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 1);
	//first int checked

	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[2]->identifier);
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 6);
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[2]->identifier);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 3);
	printf("JUMP !!%d\n", generator->label_count + 4);

	printf("LABEL !!%d\n", generator->label_count + 3);
	printf("FLOAT2INT LF@%s LF@%s\n", instruction->params[2]->identifier, instruction->params[2]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 6);
	//second int checked
	printf("LT GF@%%check0 LF@%s int@0\n", instruction->params[1]->identifier);
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("LT GF@%%check0 LF@%s int@0\n", instruction->params[2]->identifier);
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("GT GF@%%check0 LF@%s LF@%s\n", instruction->params[1]->identifier, instruction->params[2]->identifier);
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);

	printf("DEFVAR GF@%%check1\n");
	printf("STRLEN GF@%%check1 LF@%s\n", instruction->params[0]->identifier);
	printf("GT GF@%%check0 LF@%s GF@%%check1\n", instruction->params[1]->identifier);
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("GT GF@%%check0 LF@%s GF@%%check1\n", instruction->params[1]->identifier);
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("EQ GF@%%check0 LF@%s GF@%%check1\n", instruction->params[1]->identifier);
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("GT GF@%%check0 LF@%s GF@%%check1\n", instruction->params[2]->identifier);
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	//error checking done
	printf("MOVE GF@%%check1 string@\n");
	printf("LABEL !!%d\n", generator->label_count + 7);
	printf("GETCHAR GF@%%check0 LF@%s LF@%s\n", instruction->params[0]->identifier, instruction->params[1]->identifier);
	printf("CONCAT GF@%%check1 GF@%%check1 GF@%%check0\n");
	printf("ADD LF@%s LF@%s int@1\n", instruction->params[1]->identifier, instruction->params[1]->identifier);
	printf("JUMPIFNEQ !!%d LF@%s LF@%s\n", generator->label_count + 7, instruction->params[1]->identifier, instruction->params[2]->identifier);
	printf("MOVE LF@%s GF@%%check1\n", instruction->id);

	printf("JUMP !!%d\n", generator->label_count + 5);
	printf("LABEL !!%d\n", generator->label_count + 4); //error
	printf("MOVE LF@%s nil@nil\n", instruction->id);
	printf("LABEL !!%d\n", generator->label_count + 5);
	generator->label_count += 8;
}

void gen_floatval(Instruction *instruction, Generator *generator){
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 1);
	printf("MOVE LF@%s float@0x0.0p+0\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 2);

	printf("LABEL !!%d\n", generator->label_count + 1);
	printf("INT2FLOAT LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);
	printf("JUMP !!%d\n", generator->label_count + 2);

	printf("LABEL !!%d\n", generator->label_count);
	printf("MOVE LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 2);
}

void gen_intval(Instruction *instruction, Generator *generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 1);
	printf("MOVE LF@%s int@0\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 2);

	printf("LABEL !!%d\n", generator->label_count + 1);
	printf("FLOAT2INT LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);
	printf("JUMP !!%d\n", generator->label_count + 2);

	printf("LABEL !!%d\n", generator->label_count);
	printf("MOVE LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 2);
	generator->label_count += 3;
}

void gen_strval(Instruction *instruction, Generator *generator){
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
	printf("MOVE LF@%s string@\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 1);

	printf("LABEL !!%d\n", generator->label_count);
	printf("MOVE LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 1);
	generator->label_count += 2;
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
        case H_FUNC_ID:
            printf("MOVE LF@%s TF@$$retval\n", instruction->id);
            //printf("DPRINT LF@%s\n", instruction->id);
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
    printf("CALL $%s\n", instruction->operands[0]->identifier);
}

void gen_eq(Instruction *instruction, Generator *generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("TYPE GF@%%check1 LF@%s\n", instruction->operands[1]->identifier);
    printf("EQ LF@%s GF@%%check0 GF@%%check1\n", instruction->id);
    printf("JUMPIFNEQ !!%d GF@%%true LF@%s\n", generator->label_count, instruction->id);
    printf("EQ LF@%s LF@%s LF@%s\n", instruction->id, instruction->operands[0]->identifier, instruction->operands[1]->identifier);
    printf("LABEL !!%d\n", generator->label_count);
    generator->label_count++;

}

void gen_gt(Instruction *instruction, Generator *generator, char op[], bool invert) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("TYPE GF@%%check1 LF@%s\n", instruction->operands[1]->identifier);

    printf("JUMPIFNEQ !!%d GF@%%check0 GF@%%check1\n", generator->label_count + 1);
    printf("JUMPIFEQ !!%d LF@%s nil@nil\n", generator->label_count + 4, instruction->operands[0]->identifier); /* jump to end of false */

    printf("LABEL !!%d\n", generator->label_count++);

    /* operands are not null and have the same type -we can compare */
    printf("%s LF@%s LF@%s LF@%s\n", op, instruction->id, instruction->operands[0]->identifier, instruction->operands[1]->identifier);
    if (invert) printf("NOT LF@%s LF@%s\n", instruction->id, instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 4);

    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d LF@%s nil@nil\n", generator->label_count + 2, instruction->operands[0]->identifier);

    printf("JUMPIFEQ !!%d LF@%s nil@nil\n", generator->label_count + 1, instruction->operands[1]->identifier);

    printf("JUMPIFEQ $!!EXIT_7 GF@%%check0 string@string\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%check1 string@string\n");

    printf("JUMPIFNEQ !!%d GF@%%check0 string@int\n", generator->label_count);
    printf("INT2FLOAT LF@%s LF@%s\n", instruction->operands[0]->identifier, instruction->operands[0]->identifier);
    printf("JUMP !!%d\n", generator->label_count - 2);

    printf("LABEL !!%d\n", generator->label_count++);
    printf("INT2FLOAT LF@%s LF@%s\n", instruction->operands[1]->identifier, instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count - 3);  

    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d LF@%s int@0\n", generator->label_count, instruction->operands[0]->identifier);
    printf("MOVE LF@%s bool@true\n", instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 1);


    printf("LABEL !!%d\n", generator->label_count++);
    printf("MOVE LF@%s bool@false\n", instruction->id);
    printf("LABEL !!%d\n", generator->label_count++);
}

int generate(Generator *generator) {
    TData *data;
    printf(".IFJcode22\n");
    printf("DEFVAR GF@%%bool\n");
    printf("DEFVAR GF@%%int\n");
    printf("DEFVAR GF@%%float\n");
    printf("DEFVAR GF@%%string\n");
    printf("DEFVAR GF@%%nil\n");
    printf("DEFVAR GF@%%check0\n");
    printf("DEFVAR GF@%%check1\n");
    printf("DEFVAR GF@%%check2\n");
    printf("DEFVAR GF@%%index\n");
    printf("DEFVAR GF@%%true\n");
    printf("DEFVAR GF@%%false\n");
    printf("MOVE GF@%%bool string@bool\n");
    printf("MOVE GF@%%int string@int\n");
    printf("MOVE GF@%%float string@float\n");
    printf("MOVE GF@%%string string@string\n");
    printf("MOVE GF@%%nil string@nil\n");
    printf("MOVE GF@%%true bool@true\n");
    printf("MOVE GF@%%false bool@false\n");
    printf("JUMP $$main\n");

    for (long i = 0; i < generator->instruction_count; i++) {
        //individual instruction generation
        //each instruction has its own function
        switch (generator->instructions[i]->instruct) {
            case assign:
                gen_assign(generator->instructions[i]);
                break;
            case defvar:
                printf("DEFVAR LF@%s\n", generator->instructions[i]->id);
                break;
            case call:
                gen_call(generator->instructions[i]);
                break;
            case ret: //not needed?
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
                gen_gt(generator->instructions[i], generator, "LT", false);
                break;
            case gt:
                gen_gt(generator->instructions[i], generator, "GT", false);
                break;
            case eq:
                gen_eq(generator->instructions[i], generator);
                break;
            case lte:
                gen_gt(generator->instructions[i], generator, "GT", true);
                break;
            case gte:
                gen_gt(generator->instructions[i], generator, "LT", true);
                break;
            case neq:
                gen_eq(generator->instructions[i], generator);
                printf("NOT LF@%s LF@%s\n", generator->instructions[i]->id, generator->instructions[i]->id);
                break;
            case floatval:
				gen_floatval(generator->instructions[i], generator);
                break;
            case intval:
				gen_intval(generator->instructions[i], generator);
                break;
            case strval:
				gen_strval(generator->instructions[i], generator);
                break;
            case substring:
				gen_substring(generator->instructions[i], generator);
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
                printf("LABEL $!!EXIT_4\n");
                printf("EXIT int@4\n");
                printf("LABEL $!!EXIT_7\n");
                printf("EXIT int@7\n");
                printf("LABEL $!!EXIT_6\n");
                printf("EXIT int@6\n");
                break;
            case start_fn:    
                printf("LABEL $%s\n", generator->instructions[i]->operands[0]->identifier);
                printf("PUSHFRAME\n");
                printf("DEFVAR LF@$$retval\n");
                printf("MOVE LF@$$retval nil@nil\n");
                break;
                
            case end_fn_float:
                if (generator->instructions[i]->operands != NULL) {
                    printf("TYPE GF@%%check0 LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                    printf("JUMPIFNEQ $!!EXIT_6 GF@%%check0 string@float\n");
                    printf("MOVE LF@$$retval LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                }
                printf("POPFRAME\n");
                printf("RETURN\n");
                break;

            case end_fn_string:
                if (generator->instructions[i]->operands != NULL) {
                    printf("TYPE GF@%%check0 LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                    printf("JUMPIFNEQ $!!EXIT_6 GF@%%check0 string@string\n");
                    printf("MOVE LF@$$retval LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                }
                printf("POPFRAME\n");
                printf("RETURN\n");
                break;

            case end_fn_int:
                if (generator->instructions[i]->operands != NULL) {
                    printf("TYPE GF@%%check0 LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                    printf("JUMPIFNEQ $!!EXIT_6 GF@%%check0 string@int\n");
                    printf("MOVE LF@$$retval LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                }
                printf("POPFRAME\n");
                printf("RETURN\n");
                break;

            case end_fn_void:
                if (generator->instructions[i]->operands != NULL) {
                    printf("TYPE GF@%%check0 LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                    printf("JUMPIFNEQ $!!EXIT_6 GF@%%check0 string@nil\n");
                    printf("MOVE LF@$$retval LF@%s\n", generator->instructions[i]->operands[0]->identifier);
                }
                printf("POPFRAME\n");
                printf("RETURN\n");
                break;
            case while_:
                data = malloc(sizeof(TData));
                data->value = generator->label_count++;
                data->type = generator->label_count + 1;
                stack_push(generator->label_stack, data);
                printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);


                data = malloc(sizeof(TData));
                data->value = generator->label_count++;
                data->type = generator->label_count++;
                stack_push(generator->label_stack, data);
                printf("LABEL !!%d\n", stack_top(generator->label_stack)->type);

                break;
            case while_defs:
                printf("JUMP !!%d\n", generator->label_count);
                printf("LABEL !!%d\n", stack_top(generator->label_stack)->value);
                for (int j = 0; j < generator->instructions[i]->operands_count; j++) {
                    printf("DEFVAR LF@%s\n", generator->instructions[i]->operands[j]->identifier);
                }
                printf("JUMP !!%d\n", stack_pop(generator->label_stack)->type);
                printf("LABEL !!%d\n", generator->label_count++);
                break;

            case while_start:
                printf("TYPE GF@%%check0 LF@%s\n", generator->instructions[i]->id);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%string\n", generator->label_count);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%int\n", generator->label_count + 1);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%float\n", generator->label_count + 2);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%bool\n", generator->label_count + 3);
                printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);

                /* string conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                printf("STRLEN GF@%%check0 LF@%s\n", generator->instructions[i]->id);
                printf("JUMPIFEQ !!%d GF@%%check0 int@0\n", stack_top(generator->label_stack)->value);

                /* int conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                printf("JUMPIFEQ !!%d GF@%%check0 int@0\n", stack_top(generator->label_stack)->value);

                /* float conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                printf("JUMPIFEQ !!%d GF@%%check0 float@%a\n", stack_top(generator->label_stack)->value, 0.0);

                /* bool conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                printf("JUMPIFEQ !!%d GF@%%check0 bool@false\n", stack_top(generator->label_stack)->value);
                break;

            case while_end:
                printf("JUMP !!%d\n", stack_top(generator->label_stack)->type);
                printf("LABEL !!%d\n", stack_pop(generator->label_stack)->value);
                break;

            case if_:
                data = malloc(sizeof(TData));
                data->value = generator->label_count++;
                data->type = generator->label_count++;
                stack_push(generator->label_stack, data);

                printf("TYPE GF@%%check0 LF@%s\n", generator->instructions[i]->id);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%string\n", generator->label_count);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%int\n", generator->label_count + 1);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%float\n", generator->label_count + 2);
                printf("JUMPIFEQ !!%d GF@%%check0 GF@%%bool\n", generator->label_count + 3);
                printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);

                /* string conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                printf("STRLEN GF@%%check0 LF@%s\n", generator->instructions[i]->id);
                printf("JUMPIFEQ !!%d GF@%%check0 int@0\n", stack_top(generator->label_stack)->value);

                /* int conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                printf("JUMPIFEQ !!%d LF@%s int@0\n", stack_top(generator->label_stack)->value, generator->instructions[i]->id);

                /* float conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                printf("JUMPIFEQ !!%d LF@%s float@%a\n", stack_top(generator->label_stack)->value, generator->instructions[i]->id, 0.0);

                /* bool conversion */
                printf("LABEL !!%d\n", generator->label_count++);
                
                printf("JUMPIFEQ !!%d LF@%s bool@false\n", stack_top(generator->label_stack)->value, generator->instructions[i]->id);
                
                break;

            case else_:
                printf("JUMP !!%d\n", stack_top(generator->label_stack)->type);
                printf("LABEL !!%d\n", stack_top(generator->label_stack)->value);
                break;

            case else_end:
                printf("LABEL !!%d\n", stack_pop(generator->label_stack)->type);
                break;

            default:
                break;
        }
    }

    return  0;
}
