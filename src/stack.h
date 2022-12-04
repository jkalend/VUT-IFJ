// Compiler of IFJ22 language
// Faculty of Information Technology Brno University of Technology
// Authors:
// Jan Vacula (xvacul40)
// Tereza Kubincová (xkubin27)

#ifndef __STACK_H__
#define __STACK_H__
#include <stdbool.h>
#include <stdlib.h>
#include "symtable.h"


typedef struct tdata {
	unsigned int value;
	unsigned int type;
	htab_t * htab;
    htab_data_t *bucket;
} TData;

typedef struct telement {
	TData *data;
	struct telement *nextPtr;
} TElement;

typedef struct tstack {
	TElement *topPtr;
} TStack;

//allocates memory for stack
TStack *stack_init(TStack *stack);

//frees stack pointer
void stack_free(TStack *stack);

//frees all allocated elements
void stack_dispose(register TStack *stack);

//adds new element to stack
void stack_push(register TStack *stack, const TData *data);

//remove element from stack and returns its value
TData *stack_pop(register TStack *stack);

//returns state of stack
bool stack_isEmpty(const TStack *stack);

TData *stack_top(const TStack *stack);

#endif	// __STACK_H__
