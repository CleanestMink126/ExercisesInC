#include <stdio.h>

int main() {
    int x = 5;
    int y = x + 1;
    printf("%i",y);
    printf("Hello, World!\n");
    return 0;
}
/*
1.If you add optimization the assembly doesn't include the
reference to x

2. If you print x, then there is a reference regardless

3. If you use x to compute y with minimal optimization it includes
a reference to x. But with more optimization it actually precomputes
that y is 6 and stores that instead. 

*/
