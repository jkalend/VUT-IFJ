#include "hello_world.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(){
    printf("%s", hello());
    assert(strcmp(hello(), "Hello, World!\n") == 0);
}