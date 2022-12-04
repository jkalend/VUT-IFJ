// Compiler of IFJ22 language
// Faculty of Information Technology Brno University of Technology
// Authors:
// Jan Vacula (xvacul40)
// Jan Kalenda (xkalen07)

/// \file stack.c
#include "stack.h"

/// \brief Initialises a new stack
/// \param stack New stack
/// \return pointer to the new stack
TStack *stack_init(TStack *stack) {
	stack = malloc(sizeof(TStack));
	stack->topPtr = NULL;
	return stack;
}

/// \brief Frees the stack
/// \param stack Stack to be freed
void stack_free(TStack *stack) {
    stack_dispose(stack);
	free(stack);
}

/// \brief Empties the stack and frees all its items
/// \param stack Stack to be emptied
void stack_dispose(register TStack *stack) {
	register TElement temp = {.data = NULL, .nextPtr = NULL};
	while (!stack_isEmpty(stack)) {
		temp.nextPtr = stack->topPtr->nextPtr;
        if (stack->topPtr->data->htab != NULL) {
            htab_free(stack->topPtr->data->htab);
        }
        if (stack->topPtr->data != NULL) {
            free(stack->topPtr->data);
        }
		free(stack->topPtr);
		stack->topPtr = temp.nextPtr;
	}
}

/// \brief Pushes a new item to the stack
/// \param stack Stack to be pushed to
/// \param data Data to be pushed
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

/// \brief Pops the top item from the stack
/// \param stack Stack to be popped from
/// \return pointer to the popped data or NULL if the stack is empty
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

/// \brief Tells if the stack is empty
/// \param stack Stack to be checked
/// \return true if the stack is empty, false otherwise
bool stack_isEmpty(const TStack *stack) {
	if (!stack->topPtr) {
		return true;
	}
	return false;
}

/// \brief Returns the top item from the stack
/// \param stack Stack to be checked
/// \return pointer to the top item or NULL if the stack is empty
TData *stack_top(const TStack *stack) {
    if (!stack_isEmpty(stack)) {
        return stack->topPtr->data;
    }
    return NULL;
}
