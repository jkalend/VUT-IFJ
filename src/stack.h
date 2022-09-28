// stack.h
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 28.09.2022
// Přeloženo: gcc 9.4.0
#ifndef __STACK_H__
#define __STACK_H__
#include <stdbool.h>
#include <stdlib.h>

//PLACEHOLDER STRUCT
typedef struct tdata {
    int x;
    bool y;
}TData;
//END OF PLACEHOLDER

typedef struct telement {
    TData *data;
    struct telement *nextPtr;
}TElement;

typedef struct tstack{
    TElement *topPtr;
}TStack;

void stack_init(TStack *stack);

void stack_push(TStack *stack, TData *data);
//Removes one element from stack
void stack_pop(TStack *stack);
//Reads element from stack without removing it
TData *stack_top(TStack *stack);
bool stack_isEmpty(TStack *stack);

#endif  // __STACK_H__