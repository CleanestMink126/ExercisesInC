/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

void increase_stack(){
  int var3 = 7;
  printf ("Address of var3 is %p\n", &var3);
  int *p3 = malloc(16);
  int *p4 = malloc(16);
  printf ("p3 points to %p\n", p3);
  printf ("p4 points to %p\n", p4);
  /*
  It looks like it allocates 2 bytes per space allocated in malloc for both
  ints and void
  */
}

int main ()
{
    int var2 = 5;


    void *p = malloc(128);
    void *p2 = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    increase_stack();
    /*
    var3 will be on a lower virtual address space than var2 showing that the
    stack grows down
    */
    printf ("p points to %p\n", p);
    printf ("p2 points to %p\n", p2);
    /*
    p2 will be on a higher virtual address space than p showing that the heap
    grows up
    */
    printf ("s points to %p\n", s);

    return 0;
}
