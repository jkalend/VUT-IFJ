//
// Created by Kalenda, Jan on 18.11.2022.
//

#include "generator.h"
#include <stdio.h>

/// \brief Initializes the generator
/// \param generator Instance of the generator
void generator_init(Generator * restrict generator) {
    generator->label_count = 0;
    generator->instructions = malloc(sizeof(Instruction *) * 200);
    if (generator->instructions == NULL) {
        exit(BAD_INTERNAL);
    }
    generator->instruction_count = 0;
    generator->label_stack = stack_init(generator->label_stack);
}

/// \brief Frees the generator
/// \param generator Instance of the generator
void generator_free(register Generator *generator) {
    for (int i = 0; i < generator->instruction_count; i++) {
        if (generator->instructions[i]->operands != NULL) {
            free(generator->instructions[i]->operands);
        }
        generator->instructions[i]->operands = NULL;

        if (generator->instructions[i]->params != NULL) {
            free(generator->instructions[i]->params);
        }
        generator->instructions[i]->params = NULL;

        free(generator->instructions[i]);
        generator->instructions[i] = NULL;

    }
    free(generator->instructions);
    generator->instructions = NULL;
    stack_free(generator->label_stack);
    free(generator);
}

/// \brief Creates a new instruction
/// \param instruct Instruction to be added
/// \param id Identifier of a variable or function
/// \param operands Operands of the instruction
/// \param types Types of the operands
/// \param operands_count Number of operands
/// \param params Parameters of the function
/// \param params_count Number of parameters
/// \return Pointer to the instruction
Instruction *gen_instruction_constructor(InstructionType instruct,
                                         char *id,
                                         htab_pair_t **operands,
                                         DataType *types,
                                         int operands_count,
                                         htab_pair_t **params,
                                         int params_count) {
    Instruction *instruction = malloc(sizeof(Instruction));
    instruction->instruct = instruct;
    instruction->id = id;
    instruction->operands = operands;
    instruction->types = types;
    instruction->operands_count = operands_count;
    instruction->params = params;
    instruction->params_count = params_count;
    return instruction;
}

/// \brief Adds a new instruction to the generator
/// \param generator Instance of the generator
/// \param instruction Instruction to be added
void generator_add_instruction(Generator * restrict generator, Instruction *instruction) {
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

/// \brief Strlen for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_strlen(Instruction * restrict instruction, register Generator * restrict generator) {
    printf("MOVE GF@%%check1 LF@%s\n", instruction->params[0]->identifier);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%float GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%int GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check1 string@\n");

    printf("LABEL !!%d\n", generator->label_count++);
    printf("STRLEN LF@%s GF@%%check1\n", instruction->id);
}

/// \brief Substring builtin function for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_substring(register Instruction * restrict instruction, register Generator * restrict generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%float GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%int GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
	printf("JUMP $!!EXIT_4\n");

	printf("LABEL !!%d\n", generator->label_count);
	//string checked
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%string GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 1);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 2);
	printf("JUMP $!!EXIT_4\n");

	printf("LABEL !!%d\n", generator->label_count + 2);
	printf("FLOAT2INT GF@%%check1 LF@%s\n", instruction->params[1]->identifier);
	printf("JUMP !!%d\n", generator->label_count + 9);

	printf("LABEL !!%d\n", generator->label_count + 1);
	printf("MOVE GF@%%check1 LF@%s\n", instruction->params[1]->identifier);
	//first int checked

	printf("LABEL !!%d\n", generator->label_count + 9);
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[2]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%string GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 6);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 3);
	printf("JUMP $!!EXIT_4\n");

	printf("LABEL !!%d\n", generator->label_count + 3);
	printf("FLOAT2INT GF@%%check2 LF@%s\n", instruction->params[2]->identifier);
	printf("JUMP !!%d\n", generator->label_count + 10);

	printf("LABEL !!%d\n", generator->label_count + 6);
	printf("MOVE GF@%%check2 LF@%s\n", instruction->params[2]->identifier);
	//second int checked

	printf("LABEL !!%d\n", generator->label_count + 10);
	printf("LT GF@%%check0 GF@%%check1 int@0\n");
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("LT GF@%%check0 GF@%%check2 int@0\n");
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("GT GF@%%check0 GF@%%check1 GF@%%check2\n");
	printf("JUMPIFEQ !!%d GF@%%check0 bool@true\n", generator->label_count + 4);
	printf("JUMPIFEQ !!%d GF@%%check1 GF@%%check2\n", generator->label_count + 8);

	printf("STRLEN GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
	printf("GT GF@%%check3 GF@%%check1 GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%check3 bool@true\n", generator->label_count + 4);
	printf("EQ GF@%%check3 GF@%%check1 GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%check3 bool@true\n", generator->label_count + 4);
	printf("GT GF@%%check3 GF@%%check2 GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%check3 bool@true\n", generator->label_count + 4);
	//error checking done
	printf("MOVE GF@%%check0 string@\n");
	printf("LABEL !!%d\n", generator->label_count + 7);
	printf("GETCHAR GF@%%check3 LF@%s GF@%%check1\n", instruction->params[0]->identifier);
	printf("CONCAT GF@%%check0 GF@%%check0 GF@%%check3\n");
	printf("ADD GF@%%check1 GF@%%check1 int@1\n");
	printf("JUMPIFNEQ !!%d GF@%%check1 GF@%%check2\n", generator->label_count + 7);
	printf("MOVE LF@%s GF@%%check0\n", instruction->id);

	printf("JUMP !!%d\n", generator->label_count + 5);
	printf("LABEL !!%d\n", generator->label_count + 8);
	printf("MOVE LF@%s string@\n", instruction->id);

	printf("JUMP !!%d\n", generator->label_count + 5);
	printf("LABEL !!%d\n", generator->label_count + 4); //error
	printf("MOVE LF@%s nil@nil\n", instruction->id);
	printf("LABEL !!%d\n", generator->label_count + 5);
	generator->label_count += 11;
}

/// \brief Floatval builtin function for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_floatval(register Instruction * restrict instruction, register Generator * restrict generator){
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%string GF@%%check0\n");
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
    generator->label_count += 3;
}

/// \brief Intval builtin function for IFJcode22
/// \param instruction
/// \param generator
void gen_intval(register Instruction * restrict instruction, register Generator * restrict generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%string GF@%%check0\n");
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

/// \brief Strval builtin function for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_strval(register Instruction * restrict instruction, register Generator * restrict generator){
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%float GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%int GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
	printf("MOVE LF@%s string@\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 1);

	printf("LABEL !!%d\n", generator->label_count);
	printf("MOVE LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 1);
	generator->label_count += 2;
}

/// \brief Ord builtin function for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_ord(register Instruction * restrict instruction, register Generator * restrict generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%float GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%int GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);

	printf("LABEL !!%d\n", generator->label_count + 2);
	printf("MOVE LF@%s int@0\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 1);

	printf("LABEL !!%d\n", generator->label_count);
	printf("JUMPIFEQ !!%d LF@%s string@\n", generator->label_count + 2, instruction->params[0]->identifier);
	printf("STRI2INT LF@%s LF@%s int@0\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 1);
	generator->label_count += 3;

}

/// \brief Chr builtin function for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_chr(register Instruction * restrict instruction, register Generator * restrict generator) {
	printf("TYPE GF@%%check0 LF@%s\n", instruction->params[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
	printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
	printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 1);
	printf("INT2CHAR LF@%s int@0\n", instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 2);

	printf("LABEL !!%d\n", generator->label_count + 1);
	printf("FLOAT2INT LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);
	printf("INT2CHAR LF@%s LF@%s\n", instruction->id, instruction->id);
	printf("JUMP !!%d\n", generator->label_count + 2);

	printf("LABEL !!%d\n", generator->label_count);
	printf("INT2CHAR LF@%s LF@%s\n", instruction->id, instruction->params[0]->identifier);

	printf("LABEL !!%d\n", generator->label_count + 2);
	generator->label_count += 3;
}

/// \brief Write builtin function for IFJcode22
/// \param instruction Instruction to be printed
void gen_write(register Instruction * restrict instruction) {
    for (int i = 0; i < instruction->params_count; i++) {
        printf("WRITE LF@%s\n", instruction->params[i]->identifier);
    }
    printf("MOVE LF@%s nil@nil\n", instruction->id);
}

/// \brief Assign operation for IFJcode22
/// \param instruction Instruction to be printed
void gen_assign(Instruction * restrict instruction) {
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
                    break;
            }
            break;
        case H_FUNC_ID:
            printf("MOVE LF@%s TF@$$retval\n", instruction->id);
            break;
        case H_VAR:
            printf("MOVE LF@%s LF@%s\n", instruction->id, instruction->operands[0]->identifier);
            break;
        default:
            break;
    }

}

/// \brief Add operation for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_add(register Instruction * restrict instruction, register Generator * restrict generator) {
    printf("MOVE GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("MOVE GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 2);
    printf("MOVE GF@%%check1 int@0\n");
    printf("JUMP !!%d\n", generator->label_count + 2);

    printf("LABEL !!%d\n", generator->label_count++); // if op1 float
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 3); // both floats done here
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 float@%a\n", 0.0);
    printf("JUMP !!%d\n", generator->label_count + 3);

    printf("LABEL !!%d\n", generator->label_count++); // if op1 float op2 int
    printf("INT2FLOAT GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count + 2);

    printf("LABEL !!%d\n", generator->label_count++); // if op1 int or null
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 1); // both ints done here
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 int@0\n");
    printf("JUMP !!%d\n", generator->label_count + 1);

    printf("LABEL !!%d\n", generator->label_count++); // op1 int op2 float
    printf("INT2FLOAT GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);


    printf("LABEL !!%d\n", generator->label_count++); // both floats or ints
    printf("ADD LF@%s GF@%%check1 GF@%%check2\n", instruction->id);
}

/// \brief Sub operation for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_sub(register Instruction * restrict instruction, register Generator * restrict generator) {
    printf("MOVE GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("MOVE GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 2);
    printf("MOVE GF@%%check1 int@0\n");
    printf("JUMP !!%d\n", generator->label_count + 2);

    printf("LABEL !!%d\n", generator->label_count++); //if op1 float
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 3); //both floats done here
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 float@%a\n", 0.0);
    printf("JUMP !!%d\n", generator->label_count + 3);


    printf("LABEL !!%d\n", generator->label_count++); //if op1 float op2 int
    printf("INT2FLOAT GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count + 2);


    printf("LABEL !!%d\n", generator->label_count++); //if op1 int or null
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 1); //both ints done here
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 int@0\n");
    printf("JUMP !!%d\n", generator->label_count + 1);

    printf("LABEL !!%d\n", generator->label_count++); // op1 int op2 float
    printf("INT2FLOAT GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);

    printf("LABEL !!%d\n", generator->label_count++); //both floats or ints
    printf("SUB LF@%s GF@%%check1 GF@%%check2\n", instruction->id);
}

/// \brief Mul operation for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_mul(register Instruction * restrict instruction, register Generator * restrict generator) {
    printf("MOVE GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("MOVE GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 2);
    printf("MOVE GF@%%check1 int@0\n");
    printf("JUMP !!%d\n", generator->label_count + 2);

    printf("LABEL !!%d\n", generator->label_count++); //if op1 float
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 3); //both floats done here
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 float@%a\n", 0.0);
    printf("JUMP !!%d\n", generator->label_count + 3);


    printf("LABEL !!%d\n", generator->label_count++); //if op1 float op2 int
    printf("INT2FLOAT GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count + 2);


    printf("LABEL !!%d\n", generator->label_count++); //if op1 int or null
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 1); //both ints done here
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 int@0\n"); // if null
    printf("JUMP !!%d\n", generator->label_count + 1);

    printf("LABEL !!%d\n", generator->label_count++); // op1 int op2 float
    printf("INT2FLOAT GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);

    printf("LABEL !!%d\n", generator->label_count++); //both floats or ints
    printf("MUL LF@%s GF@%%check1 GF@%%check2\n", instruction->id);
}

/// \brief Div operation for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_div(register Instruction * restrict instruction, register Generator * restrict generator) {
    printf("MOVE GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("MOVE GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count + 2);
    printf("MOVE GF@%%check1 float@%a\n", 0.0);
    printf("JUMP !!%d\n", generator->label_count);

    printf("LABEL !!%d\n", generator->label_count++); //if op1 float
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count + 2); //both floats done here
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 float@%a\n", 0.0);
    printf("JUMP !!%d\n", generator->label_count + 2);

    printf("LABEL !!%d\n", generator->label_count++); //if op1 float op2 int
    printf("INT2FLOAT GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count + 1);

    printf("LABEL !!%d\n", generator->label_count++); //if op1 int
    printf("INT2FLOAT GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%string GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%int GF@%%check0\n", generator->label_count - 2); // convert to float
    printf("JUMPIFEQ !!%d GF@%%float GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 float@%a\n", 0.0);
    printf("JUMP !!%d\n", generator->label_count);

    printf("LABEL !!%d\n", generator->label_count++); //both floats or ints
    printf("DIV LF@%s GF@%%check1 GF@%%check2\n", instruction->id);
}

/// \brief Concatenation operation for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_concat(register Instruction * restrict instruction, register Generator * restrict generator) {
    printf("MOVE GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("MOVE GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%float GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%int GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check1 string@\n");

    printf("LABEL !!%d\n", generator->label_count++);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%float GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%int GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ !!%d GF@%%string GF@%%check0\n", generator->label_count);
    printf("MOVE GF@%%check2 string@\n");

    printf("LABEL !!%d\n", generator->label_count++);
    printf("CONCAT LF@%s GF@%%check1 GF@%%check2\n", instruction->id);
}

/// \brief Function call operation for IFJcode22
/// \param instruction Instruction to be printed
void gen_call(Instruction * restrict instruction) {
    printf("CREATEFRAME\n");
    for (int i = 0; i < instruction->params_count; i++) {
        printf("DEFVAR TF@%%%d\n", i);
        switch (instruction->operands[0]->params[i]) {
            case D_FLOAT:
                printf("TYPE GF@%%check0 LF@%s\n", instruction->params[i]->identifier);
                printf("JUMPIFEQ $!!EXIT_4 GF@%%string GF@%%check0\n");
                printf("JUMPIFEQ $!!EXIT_4 GF@%%int GF@%%check0\n");
                printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
                break;
            case D_INT:
                printf("TYPE GF@%%check0 LF@%s\n", instruction->params[i]->identifier);
                printf("JUMPIFEQ $!!EXIT_4 GF@%%string GF@%%check0\n");
                printf("JUMPIFEQ $!!EXIT_4 GF@%%float GF@%%check0\n");
                printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
                break;
            case D_STRING:
                printf("TYPE GF@%%check0 LF@%s\n", instruction->params[i]->identifier);
                printf("JUMPIFEQ $!!EXIT_4 GF@%%int GF@%%check0\n");
                printf("JUMPIFEQ $!!EXIT_4 GF@%%float GF@%%check0\n");
                printf("JUMPIFEQ $!!EXIT_4 GF@%%bool GF@%%check0\n");
                break;
            default:
                break;
        }
        if (instruction->operands[0]->params_strict[i]) 
            printf("JUMPIFEQ $!!EXIT_4 GF@%%nil GF@%%check0\n");

        printf("MOVE TF@%%%d LF@%s\n", i, instruction->params[i]->identifier);
    }
    printf("CALL $%s\n", instruction->operands[0]->identifier);
    printf("MOVE LF@%s TF@$$retval\n", instruction->id);
}

/// \brief Equal operation for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_eq(register Instruction * restrict instruction, Generator * restrict generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("TYPE GF@%%check1 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check1\n");
    printf("EQ LF@%s GF@%%check0 GF@%%check1\n", instruction->id);
    printf("JUMPIFNEQ !!%d GF@%%true LF@%s\n", generator->label_count, instruction->id);
    printf("EQ LF@%s LF@%s LF@%s\n", instruction->id, instruction->operands[0]->identifier, instruction->operands[1]->identifier);
    printf("LABEL !!%d\n", generator->label_count++);
}

/// \brief > < >= <= operations for IFJcode22
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
/// \param op Which operation to print
/// \param invert Use inverted operation
void gen_gt(register Instruction * restrict instruction, register Generator * restrict generator, char op[], bool invert) {
    printf("MOVE GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("MOVE GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);

    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("TYPE GF@%%check3 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check0\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%bool GF@%%check3\n");

    printf("JUMPIFNEQ !!%d GF@%%check0 GF@%%check3\n", generator->label_count + 1);
    printf("JUMPIFEQ !!%d LF@%s nil@nil\n", generator->label_count + 6, instruction->operands[0]->identifier); /* jump to end of false */

    printf("LABEL !!%d\n", generator->label_count++);

    /* operands are not null and have the same type -we can compare */
    printf("%s LF@%s GF@%%check1 GF@%%check2\n", op, instruction->id);
    if (invert) printf("NOT LF@%s LF@%s\n", instruction->id, instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 6);

    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d LF@%s nil@nil\n", generator->label_count + 4, instruction->operands[0]->identifier);

    printf("JUMPIFEQ !!%d LF@%s nil@nil\n", generator->label_count + 1, instruction->operands[1]->identifier);

    printf("JUMPIFEQ $!!EXIT_7 GF@%%check0 string@string\n");
    printf("JUMPIFEQ $!!EXIT_7 GF@%%check3 string@string\n");

    printf("JUMPIFNEQ !!%d GF@%%check0 string@int\n", generator->label_count);
    printf("INT2FLOAT GF@%%check1 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMP !!%d\n", generator->label_count - 2);

    printf("LABEL !!%d\n", generator->label_count++);
    printf("INT2FLOAT GF@%%check2 LF@%s\n", instruction->operands[1]->identifier);
    printf("JUMP !!%d\n", generator->label_count - 3);  

    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d GF@%%check0 string@float\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%check0 string@string\n", generator->label_count + 1);
    printf("JUMPIFEQ !!%d GF@%%check1 int@0\n", generator->label_count + 2);

    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d GF@%%check1 float@%a\n", generator->label_count + 1, 0.0);

    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d GF@%%check1 string@\n", generator->label_count);


    printf("MOVE LF@%s bool@true\n", instruction->id);
    if (invert) printf("NOT LF@%s LF@%s\n", instruction->id, instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 1);

    printf("LABEL !!%d\n", generator->label_count++);
    printf("MOVE LF@%s bool@false\n", instruction->id);
    if (invert) printf("NOT LF@%s LF@%s\n", instruction->id, instruction->id);
    printf("LABEL !!%d\n", generator->label_count++);
}

/// \brief IFJcode22 variable definition check
/// \param instruction Instruction to be printed
/// \param operand_not_param If the checked instruction uses operands and not parameters
void gen_check(register const Instruction *instruction, bool operand_not_param) {
    if (operand_not_param) {
        for (int i = 0; i < instruction->operands_count; i++) {
            printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[i]->identifier);
            printf("EQ GF@%%check0 GF@%%check0 string@\n");
            printf("JUMPIFEQ $!!EXIT_5 GF@%%check0 bool@true\n");
        }
    } else {
        for (int i = 0; i < instruction->params_count; i++) {
            printf("TYPE GF@%%check0 LF@%s\n", instruction->params[i]->identifier);
            printf("EQ GF@%%check0 GF@%%check0 string@\n");
            printf("JUMPIFEQ $!!EXIT_5 GF@%%check0 bool@true\n");
        }
    }
}

/// \brief Start of the function definition
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_start_fn(register const Instruction * restrict instruction, Generator * restrict generator) {
    TData * restrict data = malloc(sizeof(TData));
    data->value = generator->label_count++;
    data->type = generator->label_count++;
    data->htab = NULL;
    data->bucket = instruction->operands[0];
    stack_push(generator->label_stack, data);
    printf("JUMP !!%d\n", stack_top(generator->label_stack)->type);
    printf("LABEL $%s\n", instruction->operands[0]->identifier);
    printf("PUSHFRAME\n");

    for (int j = 0; j < instruction->operands[0]->param_count; j++) {
        printf("DEFVAR LF@%s\n", instruction->operands[0]->param_names[j]);
        printf("MOVE LF@%s LF@%%%d\n", instruction->operands[0]->param_names[j], j);
    }

    printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);

    printf("LABEL !!%s\n", instruction->operands[0]->identifier);

    printf("DEFVAR LF@$$retval\n");
    printf("MOVE LF@$$retval nil@nil\n");
}

/// \brief definition of all variables in the function
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
/// \param parser Instance of the parser
void gen_fn_defs(register const Instruction * restrict instruction, Generator * restrict generator, parser_t * restrict parser) {
    const TData *data = stack_pop(generator->label_stack);
    printf("JUMP !!%d\n", generator->label_count);
    printf("LABEL !!%d\n", data->value);
    for (int j = 0; j < instruction->operands_count; j++) {
        printf("DEFVAR LF@%s\n", instruction->operands[j]->identifier);
    }
    printf("JUMP !!%s\n", data->bucket->identifier);
    printf("LABEL !!%d\n", generator->label_count++);
    printf("LABEL !!%d\n", data->type);
    stack_push(parser->garbage_bin, data);
}

/// \brief End of a float function definition
/// \param instruction Instruction to be printed
void gen_end_fn_float(register const Instruction * restrict instruction) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@string\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@int\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@bool\n");
    if (instruction->operands[0]->strict_return) {
        printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@nil\n");
    }
    printf("MOVE LF@$$retval LF@%s\n", instruction->operands[0]->identifier);
    printf("POPFRAME\n");
    printf("RETURN\n");
}

/// \brief End of a string function definition
/// \param instruction Instruction to be printed
void gen_end_fn_string(register const Instruction * restrict instruction) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@int\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@float\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@bool\n");
    if (instruction->operands[0]->strict_return) {
        printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@nil\n");
    }
    printf("MOVE LF@$$retval LF@%s\n", instruction->operands[0]->identifier);
    printf("POPFRAME\n");
    printf("RETURN\n");
}

/// \brief End of a int function definition
/// \param instruction Instruction to be printed
void gen_end_fn_int(register const Instruction * restrict instruction) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@string\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@float\n");
    printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@bool\n");
    if (instruction->operands[0]->strict_return) {
        printf("JUMPIFEQ $!!EXIT_4 GF@%%check0 string@nil\n");
    }
    printf("MOVE LF@$$retval LF@%s\n", instruction->operands[0]->identifier);
    printf("POPFRAME\n");
    printf("RETURN\n");
}

/// \brief End of a void function definition
/// \param instruction Instruction to be printed
void gen_end_fn_void(register const Instruction * restrict instruction) {
    if (instruction->operands != NULL) {
        printf("TYPE GF@%%check0 LF@%s\n", instruction->operands[0]->identifier);
        printf("JUMPIFNEQ $!!EXIT_6 GF@%%check0 string@nil\n");
        printf("MOVE LF@$$retval LF@%s\n", instruction->operands[0]->identifier);
    }
    printf("POPFRAME\n");
    printf("RETURN\n");
}

/// \brief Start of a while loop
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_while_(const Instruction * restrict instruction, Generator * restrict generator) {
    TData *data = NULL;
    if (instruction->params_count) {
        data = malloc(sizeof(TData));
        data->value = generator->label_count++;
        data->type = generator->label_count + 1;
        data->htab = NULL;
        data->bucket = NULL;
        stack_push(generator->label_stack, data);
        printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);
    }

    data = malloc(sizeof(TData));
    data->value = generator->label_count++;
    data->type = generator->label_count++;
    data->htab = NULL;
    data->bucket = NULL;
    stack_push(generator->label_stack, data);
    printf("LABEL !!%d\n", stack_top(generator->label_stack)->type);
}

/// \brief Definiton of variables in a while loop
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
/// \param parser Instance of the parser
void gen_while_defs(register const Instruction * restrict instruction, Generator * restrict generator, parser_t * restrict parser) {
    const TData *data = stack_pop(generator->label_stack);
    printf("JUMP !!%d\n", generator->label_count);
    printf("LABEL !!%d\n", data->value);
    for (int j = 0; j < instruction->operands_count; j++) {
        printf("DEFVAR LF@%s\n", instruction->operands[j]->identifier);
    }
    printf("JUMP !!%d\n", data->type);
    printf("LABEL !!%d\n", generator->label_count++);
    stack_push(parser->garbage_bin, data);
}

/// \brief Evaluation of the while loop condition
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_while_start(register Instruction * restrict instruction, register Generator * restrict generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->id);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%string\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%int\n", generator->label_count + 1);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%float\n", generator->label_count + 2);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%bool\n", generator->label_count + 3);
    printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);

    /* string conversion */
    printf("LABEL !!%d\n", generator->label_count++);
    printf("STRLEN GF@%%check0 LF@%s\n", instruction->id);
    printf("JUMPIFEQ !!%d GF@%%check0 int@0\n", stack_top(generator->label_stack)->value);
    printf("JUMPIFEQ !!%d LF@%s string@0\n", stack_top(generator->label_stack)->value, instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 3);

    /* int conversion */
    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d LF@%s int@0\n", stack_top(generator->label_stack)->value, instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 2);

    /* float conversion */
    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d LF@%s float@%a\n", stack_top(generator->label_stack)->value, instruction->id, 0.0);
    printf("JUMP !!%d\n", generator->label_count + 1);

    /* bool conversion */
    printf("LABEL !!%d\n", generator->label_count++);

    printf("JUMPIFEQ !!%d LF@%s bool@false\n", stack_top(generator->label_stack)->value, instruction->id);
    printf("LABEL !!%d\n", generator->label_count++);
}

/// \brief End of a while loop
/// \param generator Instance of the generator
/// \param parser Instance of the parser
void gen_while_end(Generator * restrict generator, parser_t * restrict parser) {
    const TData *data = stack_pop(generator->label_stack);
    printf("JUMP !!%d\n", data->type);
    printf("LABEL !!%d\n", data->value);
    stack_push(parser->garbage_bin, data);
}

/// \brief Start of an if block
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_if_start(const Instruction * restrict instruction, Generator * restrict generator) {
    TData *data = NULL;
    if (instruction->params_count) {
        data = malloc(sizeof(TData));
        data->value = generator->label_count++;
        data->type = generator->label_count++;
        data->htab = NULL;
        data->bucket = NULL;
        stack_push(generator->label_stack, data);
        printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);
        printf("LABEL !!%d\n", stack_top(generator->label_stack)->type);
    }

    data = malloc(sizeof(TData));
    data->value = generator->label_count++;
    data->type = generator->label_count++;
    data->htab = NULL;
    data->bucket = NULL;
    stack_push(generator->label_stack, data);
}

/// \brief Evaluation of an if block condition
/// \param instruction Instruction to be printed
/// \param generator Instance of the generator
void gen_if_(register const Instruction * restrict instruction, register Generator * restrict generator) {
    printf("TYPE GF@%%check0 LF@%s\n", instruction->id);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%string\n", generator->label_count);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%int\n", generator->label_count + 1);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%float\n", generator->label_count + 2);
    printf("JUMPIFEQ !!%d GF@%%check0 GF@%%bool\n", generator->label_count + 3);
    printf("JUMP !!%d\n", stack_top(generator->label_stack)->value);

    /* string conversion */
    printf("LABEL !!%d\n", generator->label_count++);
    printf("STRLEN GF@%%check0 LF@%s\n", instruction->id);
    printf("JUMPIFEQ !!%d GF@%%check0 int@0\n", stack_top(generator->label_stack)->value);
    printf("JUMPIFEQ !!%d LF@%s string@0\n", stack_top(generator->label_stack)->value, instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 3);

    /* int conversion */
    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d LF@%s int@0\n", stack_top(generator->label_stack)->value, instruction->id);
    printf("JUMP !!%d\n", generator->label_count + 2);
    /* float conversion */
    printf("LABEL !!%d\n", generator->label_count++);
    printf("JUMPIFEQ !!%d LF@%s float@%a\n", stack_top(generator->label_stack)->value, instruction->id, 0.0);
    printf("JUMP !!%d\n", generator->label_count + 1);

    /* bool conversion */
    printf("LABEL !!%d\n", generator->label_count++);

    printf("JUMPIFEQ !!%d LF@%s bool@false\n", stack_top(generator->label_stack)->value, instruction->id);
    printf("LABEL !!%d\n", generator->label_count++);
}

/// \brief Start of an else block
/// \param generator Instance of the generator
void gen_else_(const Generator *generator) {
    printf("JUMP !!%d\n", stack_top(generator->label_stack)->type);
    printf("LABEL !!%d\n", stack_top(generator->label_stack)->value);
}

/// \brief Main function of the generator
/// \param generator Instance of the generator
/// \param parser Instance of the parser
void generate(register Generator * restrict generator, register struct parser_t * restrict parser) {
    const TData *data = NULL;
    printf(".IFJcode22\n");
    printf("DEFVAR GF@%%bool\n");
    printf("DEFVAR GF@%%int\n");
    printf("DEFVAR GF@%%float\n");
    printf("DEFVAR GF@%%string\n");
    printf("DEFVAR GF@%%nil\n");
    printf("DEFVAR GF@%%check0\n");
    printf("DEFVAR GF@%%check1\n");
    printf("DEFVAR GF@%%check2\n");
    printf("DEFVAR GF@%%check3\n");
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
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");


    for (long i = 0; i < generator->instruction_count; i++) {
        switch (generator->instructions[i]->instruct) {
            case assign:
                if (generator->instructions[i]->operands[0]->type == H_VAR) {
                    gen_check(generator->instructions[i], true);
                }
                gen_assign(generator->instructions[i]);
                break;

            case defvar:
                printf("DEFVAR LF@%s\n", generator->instructions[i]->id);
                break;

            case call:
                gen_check(generator->instructions[i], false);
                gen_call(generator->instructions[i]);
                break;

            case addition:
                gen_check(generator->instructions[i], true);
                gen_add(generator->instructions[i], generator);
                break;

            case sub:
                gen_check(generator->instructions[i], true);
                gen_sub(generator->instructions[i], generator);
                break;

            case mul:
                gen_check(generator->instructions[i], true);
                gen_mul(generator->instructions[i], generator);
                break;

            case div_:
                gen_check(generator->instructions[i], true);
                gen_div(generator->instructions[i], generator);
                break;

            case idiv: //never happens
                gen_div(generator->instructions[i], generator);
                break;

            case lt:
                gen_check(generator->instructions[i], true);
                gen_gt(generator->instructions[i], generator, "LT", false);
                break;

            case gt:
                gen_check(generator->instructions[i], true);
                gen_gt(generator->instructions[i], generator, "GT", false);
                break;

            case eq:
                gen_check(generator->instructions[i], true);
                gen_eq(generator->instructions[i], generator);
                break;

            case lte:
                gen_check(generator->instructions[i], true);
                gen_gt(generator->instructions[i], generator, "GT", true);
                break;

            case gte:
                gen_check(generator->instructions[i], true);
                gen_gt(generator->instructions[i], generator, "LT", true);
                break;

            case neq:
                gen_check(generator->instructions[i], true);
                gen_eq(generator->instructions[i], generator);
                printf("NOT LF@%s LF@%s\n", generator->instructions[i]->id, generator->instructions[i]->id);
                break;

            case floatval:
                gen_check(generator->instructions[i], false);
				gen_floatval(generator->instructions[i], generator);
                break;

            case intval:
                gen_check(generator->instructions[i], false);
				gen_intval(generator->instructions[i], generator);
                break;

            case strval:
                gen_check(generator->instructions[i], false);
				gen_strval(generator->instructions[i], generator);
                break;

            case substring:
                gen_check(generator->instructions[i], false);
				gen_substring(generator->instructions[i], generator);
                break;

            case ord:
                gen_check(generator->instructions[i], false);
				gen_ord(generator->instructions[i], generator);
                break;

            case chr:
                gen_check(generator->instructions[i], false);
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
                gen_check(generator->instructions[i], false);
                gen_write(generator->instructions[i]);
                break;

            case concat:
                gen_check(generator->instructions[i], true);
                gen_concat(generator->instructions[i], generator);
                break;

            case strlen_:
                gen_check(generator->instructions[i], false);
                gen_strlen(generator->instructions[i], generator);
                break;

            case end:
                printf("EXIT int@0\n");
                printf("LABEL $!!EXIT_4\n");
                printf("EXIT int@4\n");
                printf("LABEL $!!EXIT_7\n");
                printf("EXIT int@7\n");
                printf("LABEL $!!EXIT_6\n");
                printf("EXIT int@6\n");
                printf("LABEL $!!EXIT_5\n");
                printf("EXIT int@5\n");
                break;

            case start_fn:
                gen_start_fn(generator->instructions[i], generator);
                break;

            case fn_defs:
                gen_fn_defs(generator->instructions[i], generator, parser);
                break;
                
            case end_fn_float:
                gen_check(generator->instructions[i], true);
                gen_end_fn_float(generator->instructions[i]);
                break;

            case end_fn_string:
                gen_check(generator->instructions[i], true);
                gen_end_fn_string(generator->instructions[i]);
                break;

            case end_fn_int:
                gen_check(generator->instructions[i], true);
                gen_end_fn_int(generator->instructions[i]);
                break;

            case err_quit4:
                printf("JUMP $!!EXIT_4\n");
                break;

            case err_quit6:
                printf("JUMP $!!EXIT_6\n");
                break;

            case end_fn_void:
                gen_check(generator->instructions[i], true);
                gen_end_fn_void(generator->instructions[i]);
                break;

            case while_:
                gen_while_(generator->instructions[i], generator);
                break;

            case while_defs:
                gen_while_defs(generator->instructions[i], generator, parser);
                break;

            case while_start:
                gen_while_start(generator->instructions[i], generator);
                break;

            case while_end:
                gen_while_end(generator, parser);
                break;

            case if_start:
                gen_if_start(generator->instructions[i], generator);
                break;

            case if_:
                gen_if_(generator->instructions[i], generator);
                break;

            case else_:
                gen_else_(generator);
                break;

            case else_end:
                data = stack_pop(generator->label_stack);
                printf("LABEL !!%d\n", data->type);
                stack_push(parser->garbage_bin, data);
                break;
            case exit_success:
                printf("EXIT int@0\n");
                break;
            default:
                break;
        }
    }

    // free all the Instruction structs and the Generator struct
    generator_free(generator);
}
