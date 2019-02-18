/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
This should populate an array with all 42s and then print them
*/
int *foo() {
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    /*
    The problem of "function returns address of local variable" comes from here
    where array is declared in local scope (aka however many bits away from
    the start of the current stack frame). So that won't make sense in other
    contexts.s
    */
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    printf("%p\n", array);
    /*
    printing out the similar bar function hows that the arrays have the same
    address space because they were declared in local scope
    */

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
