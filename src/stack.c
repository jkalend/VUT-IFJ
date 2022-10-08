// stack.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 28.09.2022
// Přeloženo: gcc 9.4.0

#include "stack.h"


TStack *stack_init(TStack *stack) {
    stack = malloc(sizeof(TStack));
    return stack;
}

void stack_free(TStack *stack) {
    free(stack);
}

void stack_push(TStack *stack, TData *data) {
    TElement *newElement = malloc(sizeof(TElement));
    if(newElement == NULL) {
        exit(1);
    }
    newElement->data = data;
    newElement->nextPtr = stack->topPtr;
    stack->topPtr = newElement;
}


TData *stack_pop(TStack *stack) {
    if(!stack_isEmpty(stack)) {
        TData *data = stack->topPtr->data;
        TElement *temp = stack->topPtr;
        stack->topPtr = temp->nextPtr;
        free(temp);
        return data;
    }
}

bool stack_isEmpty(TStack *stack){
    if(!stack->topPtr) {
        return true;
    }
    return false;
}