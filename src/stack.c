
// stack.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 28.09.2022
// Přeloženo: gcc 9.4.0

#include "stack.h"

TStack *stack_init(TStack *stack) {
	stack = malloc(sizeof(TStack));
	stack->topPtr = NULL;
	return stack;
}

void stack_free(TStack *stack) {
	free(stack);
}

void stack_dispose(register TStack *stack) {
	register TElement temp = {.data = NULL, .nextPtr = NULL};
	while (!stack_isEmpty(stack)) {
		temp.nextPtr = stack->topPtr->nextPtr;
		free(stack->topPtr);
		stack->topPtr = temp.nextPtr;
	}
    //stack_free(stack);
}

void stack_push(register TStack *stack, const TData *data) {
	TElement *newElement = malloc(sizeof(TElement));
	if (newElement == NULL) {
		stack_dispose(stack);
		exit(1);
	}
	newElement->data = (TData *)data;
	newElement->nextPtr = stack->topPtr;
	stack->topPtr = newElement;
}

TData *stack_pop(register TStack *stack) {
	if (!stack_isEmpty(stack)) {
		TData *data = stack->topPtr->data;
		TElement *temp = stack->topPtr;
		stack->topPtr = temp->nextPtr;
		free(temp);
		return data;
	}
	return NULL;
}

bool stack_isEmpty(const TStack *stack) {
	if (!stack->topPtr) {
		return true;
	}
	return false;
}

TData *stack_top(const TStack *stack) {
    if (!stack_isEmpty(stack)) {
        return stack->topPtr->data;
    }
    return NULL;
}
