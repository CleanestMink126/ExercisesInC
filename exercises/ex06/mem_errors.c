/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

int main()
{
    // int never_allocated;
    int *free_twice = malloc(sizeof (int));
    int *use_after_free = malloc(sizeof (int));
    int *never_free = malloc(sizeof (int));
    int array1[100];
    int *array2 = malloc(100 * sizeof (int));

    //This will work but will read random data
    read_element(array1, -1);
    read_element(array1, 100);

    //This can error because it is checking unallocated memory
    read_element(array2, 0);
    read_element(array2, 99);

    // and it catches use after free
    free(use_after_free);
    //Nope
    // *use_after_free = 17;

    // never_free is definitely lost
    *never_free = 17;
    //Make it free
    free(never_free);

    // the following line would generate a warning
    // free(&never_allocated);

    // but this one doesn't
    //So...we dont do that
    // free_anything(&never_allocated);

    free(free_twice);
    //And let's not do that twice
    // free(free_twice);'
    //And we have to free array2
    free(array2);
    //lit no errors
    return 0;
}
