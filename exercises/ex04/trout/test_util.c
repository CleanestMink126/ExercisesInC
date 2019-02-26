/* Example code for Software Systems at Olin College.

Copyright 2017 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "minunit.h"
#include "trout.h"
#include "util.h"


int tests_run = 0;

static char *test1() {
    struct timeval in;
    struct timeval out;
    out.tv_usec = 1000;
    in.tv_usec = 5;
    out.tv_sec = 1000;
    in.tv_sec = 5;
    tv_sub(&out, &in);
    char *message = "test1 failed: tv_sub(1000, 5) should return 995";
    mu_assert(message, out.tv_sec == 995);
    return NULL;
}

static char *test2() {
  struct timeval in;
  struct timeval out;
  out.tv_usec = 50;
  in.tv_usec = 100;
  out.tv_sec = 50;
  in.tv_sec = 100;
  tv_sub(&out, &in);
  char *message = "test2 failed: tv_sub(50,100) should return -51";
  mu_assert(message, out.tv_sec == -51);
  return NULL;
}

static char *test3() {
  struct timeval in;
  struct timeval out;
  out.tv_usec = 1000;
  in.tv_usec = 10000;
  out.tv_sec = 1000;
  in.tv_sec = 10000;
  tv_sub(&out, &in);
  char *message = "test3 failed: tv_sub(1000, 10000) should return -9001";
  mu_assert(message, out.tv_sec == -9001);
  return NULL;
}

static char * all_tests() {
    mu_run_test(test1);
    mu_run_test(test2);
    mu_run_test(test3);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
