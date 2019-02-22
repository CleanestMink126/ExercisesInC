#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  char action[] = "w";
  char ch;
  //
  while ((ch = getopt(argc, argv, "a")) != EOF){
    if(ch == 'a'){
      action[0] = 'a';
    }
    argc -= optind;
    argv += optind;
  }
  //Declare Files
  //Return if we can't open a file
  FILE* files[argc];
  for (int count = 0; count < argc; count++){
    files[count] = fopen(argv[count], action);
    if(!files[count]){
      printf("Improper Input");
      exit(1);
    }
  }
  //Start reading stdin
  char buffer[100];
  while(feof(stdin)){
    scanf("%s100", buffer);
    for(int count = 0; count < argc; count++){
      fprintf(files[count], "%s100", buffer);
    }
    printf("%s100",buffer);
  }
  //Close files
  for(int count = 0; count < argc; count++){
    fclose(files[count]);
  }
}
//Reflection
//@Vicky or @Emily I think god was on my side for this program ... it somehow
//worked perfectly the first time... or I am a god. Cult applications open next week
/*
Looking up the inputs and outputs of the standard functions slowed me down a
good bit. So remembering how to get arguments, open files, write to files,etc.
was the bigest time sink. Besides that I would do most of the other stuff about
the same, Cutting it up into smaller functions might make it more readable

-In the professional solutions it's hard to see much as it's not very readable.
-They did a lot more with pointers than I did. They also had a lot of the heavy
lifting that was done inside the conditionals
eg
     while ((rval = read(STDIN_FILENO, buf, BSIZE)) > 0)

So they both do work and do a check in the same line, which probably still makes
a difference after compilation.
-they use the open and read rather than fopen and scanf
-I do see some ternary operators :)
-I also see significantly less self reflection in the professional solution.
*/
