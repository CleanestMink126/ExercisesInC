/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

//Check variable for global segment
int global_int = 10;

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;
    //init our stack int
    int stack_int = 10;
    //init our heap int
    int* heap_int = malloc(sizeof(int));
    *heap_int =10;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if(pid == 0){
            child_code(i+10);//make sure parent executes first
            printf("Child code:\n Global:%i\nHeap:%i\nStack:%i\n\n",global_int,stack_int, *heap_int);
            exit(i+10);
        }
    }

    /* parent continues */
    //The goal here is to initialize some variables in the global, stack, and
    //heap sections. We then spawn the child processes which will wait for a bit
    //so that we can make sure all ofthe parent code executes. The parent code
    //will then modify the variables and print them out. If the child processes
    //print out the same number, they share a space, otherwise they dont.
    printf("Hello from the parent.\n");
    global_int = 9;
    stack_int = 9;
    *heap_int = 9;
    printf("Parent code:\n Global:%i\nHeap:%i\nStack:%i\n\n",global_int,stack_int, *heap_int);

    //RESULTS
    //The parent process printed out all 9s (modified) as expexted while the
    //child processes printed out the unmodified 10s meaning they copy the
    //heap, stack and global segments instead of using the original ones. 

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
