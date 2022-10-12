//
// Created by Kalenda, Jan on 01.10.2022.
//

#include "stack.h"
#include <assert.h>

int test1(TStack *S, TData *a, TData *b, TData *c) {
	assert(stack_isEmpty(S));
	//    if (!stack_isEmpty(S)) {
	//        return 1;
	//    }
	stack_push(S, a);
	assert(!stack_isEmpty(S));
	//    if (stack_isEmpty(S)) {
	//        return 1;
	//    }
	stack_push(S, c);
	assert(!stack_isEmpty(S));
	//    if (stack_isEmpty(S)) {

	//        return 1;
	//    }
	stack_push(S, b);
	assert(!stack_isEmpty(S));
	//    if (stack_isEmpty(S)) {
	//        return 1;
	//    }
	assert(stack_pop(S) == b);
	//    if (stack_top(S) != a) {
	//        return 1;
	//    }
	assert(stack_pop(S) == c);
	//    if (stack_top(S) != b) {
	//        return 1;
	//    }
	assert(stack_pop(S) == a);
	//    if (stack_top(S) != c) {
	//        return 1;
	//    }
	return 0;
}

int test2(TStack *S, TData *a, TData *b, TData *c) {
	assert(stack_isEmpty(S));
	//    if (!stack_isEmpty(S)) {
	//        return 1;
	//    }
	stack_push(S, a);
	assert(!stack_isEmpty(S));
	//    if (stack_isEmpty(S)) {
	//        return 1;
	//    }

	assert(stack_pop(S) == a);

	//    if (stack_top(S) != a) {
	//        return 1;
	//    }
	stack_push(S, b);
	assert(!stack_isEmpty(S));
	//    if (stack_isEmpty(S)) {
	//        return 1;
	//    }
	assert(stack_pop(S) == b);
	//    if (stack_top(S) != b) {
	//        return 1;
	//    }
	stack_push(S, c);
	assert(!stack_isEmpty(S));
	//    if (stack_isEmpty(S)) {
	//        return 1;
	//    }

	assert(stack_pop(S) == c);
	//    if (stack_top(S) != c) {
	//        return 1;
	//    }

	assert(stack_isEmpty(S));
	//    if (!stack_isEmpty(S)) {
	//        return 1;
	//    }
	return 0;
}

int main(void) {
	TStack *S;	//= malloc(sizeof(TStack));
	TData *a = malloc(sizeof(TData));
	TData *b = malloc(sizeof(TData));
	TData *c = malloc(sizeof(TData));
	a->x = 5;
	b->x = 6;
	c->x = 7;

	S = stack_init(S);
	test1(S, a, b, c);
	test2(S, a, b, c);
	stack_free(S);
}