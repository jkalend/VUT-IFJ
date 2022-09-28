// stackTests.c
// Řešení: IFJ projekt
// Autor: Jan Vacula xvacul40, FIT
// Vytvořeno: 28.09.2022
// Přeloženo: gcc 9.4.0

#include "stack.h"
#include <stdio.h>

// NA ASSERTY NEZBYL BUDGET

int main()
{
    TData *a = malloc(sizeof(TData));
    a->x = 5;
    TData *check = malloc(sizeof(TData));
    TStack *S = malloc(sizeof(TStack));

    stack_init(S);//SUKSESS I GUESS

    /*Empty stack tests*/
    //check = stack_top(S);
    //stack_pop(S);
    //printf("%d\n", check->x );
    //printf("%d\n", stack_isEmpty(S));

    
    stack_push(S, a);
    printf("%d\n", stack_isEmpty(S));
    /*check = stack_top(S);
    printf("%d\n", check->x );
    stack_pop(S);
    printf("%d\n", check->x);
    */  
}