// stack.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 28.09.2022
// Přeloženo: gcc 9.4.0

#include "stack.h"
//#include <stdbool.h>
#include <stdlib.h>

void stack_init(TStack *stack)
{
    stack->topPtr = NULL;
}



void stack_push(TStack *stack, TData *data)
{
    TElement *newElement = malloc(sizeof(TElement*));
    if(newElement == NULL)
    {
        //SOME ERROR HANDLING FEATURE TBD
        exit(1);
    }
    newElement->data = data; //PLACEHOLDER 
    newElement->nextPtr = stack->topPtr;
    stack->topPtr = newElement;
}

void stack_pop(TStack *stack)
{
    TElement *temp = stack->topPtr->nextPtr;
    stack->topPtr = temp->nextPtr;
    free(temp);

}

TData stack_top(TStack *stack)
{
    return *stack->topPtr->data;
}

bool stack_isEmpty(TStack *stack)
{
    if(stack->topPtr == NULL)
    {
        return false;
    }
    return true;
}