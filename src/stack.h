// stack.h
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 28.09.2022
// Přeloženo: gcc 9.4.0
#ifndef __STACK_H__
#define __STACK_H__
#include <stdbool.h>

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

void stack_init();
void stack_push();
void stack_pop();
TData stack_top();
bool stack_isEmpty();

#endif  // __STACK_H__