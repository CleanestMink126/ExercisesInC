/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

//Butchered from the example in the Regex documentation
//Checks a given string against a regular expression and returns status
int match(char string[], regex_t re){
  int status;
  status = regexec(&re, string, (size_t) 0, NULL, 0);
  if (status != 0) {
      return(0);      /* doesn't match */
  }
  return(1);

}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
  regex_t re;
  //Check for valid expression and tell to return 1/0
  //Initializes re
  if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
      printf("Not a valid regular expresson");
      return;      /* report error */
  }
  //Run through the tracks and check for pattern
  for (int i=0; i<NUM_TRACKS; i++) {
      if (match(tracks[i], re)) {
          printf("Track %i: '%s'\n", i, tracks[i]);
      }
  }
  regfree(&re);//Free up allocated space
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    find_track_regex(search_for);
    //find_track_regex(search_for);

    return 0;
}
