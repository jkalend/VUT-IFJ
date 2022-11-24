
// stack.h
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 28.09.2022
// Přeloženo: gcc 9.4.0
#ifndef __STACK_H__
#define __STACK_H__
#include <stdbool.h>
#include <stdlib.h>
#include "htab.h"



typedef struct tdata {
	unsigned int value;
	unsigned int type;
	htab_t * htab;
    htab_pair_t *bucket;
	struct Instruction * in_while;
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
void stack_dispose(TStack *stack);

//adds new element to stack
void stack_push(TStack *stack, const TData *data);

//remove element from stack and returns its value
TData *stack_pop(TStack *stack);

//returns state of stack
bool stack_isEmpty(TStack *stack);

TData *stack_top(TStack *stack);

#endif	// __STACK_H__
