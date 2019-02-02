/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Accept numbers input by the user (one per line) until the EOF character is present. Then add
up all the numbers.

Requirements:
It should convert the numbers from input strings to integers and store the integers in an array.
Error messages if the user enters something that exceeds buffer length
 or can't be converted to an integer.
It should also produce an error message if the array overflows
*/
int return_status;
int number_holder;
int max_array_size = 20;

/*
Run through a given array and sum the elements until size
*/
int total_array(int* array,int size){
  int total = 0;
  while(size > 0){
    total += array[size-1];
    printf("Val: %i\n",array[size-1]);
    size--;
  }
  return total;
}

/*
Prompt the user for a number, parse the input for EOF and buffer overflow
returning -1 and -2 respectively.
Also return -2 if the input cannot be converted to a number
If everything works, return the number.
*/
int get_number(){
  int max_input_size = 10;
  char p[max_input_size];

  printf("Enter an integer: ");
  return_status= scanf("%10s",p);
  if(return_status == -1){
    printf("End of Field\n");
    return -1;
  }else if(strlen(p) == max_input_size){
    printf("Input (probably?) exceeds buffer length.\n");
    fseek(stdin,0,SEEK_END);
    return -2;
  }

  number_holder = atoi(p);
  if(number_holder == 0 && p[0] != '0'){
    printf("Can't read input\n");
    return -2;
  }
  return number_holder;
}

/*
Loop prompting the use for a number, if get_number returns successfully, add the number
onto the array and increment size.
If size is too big or EOF, break.
Then calculate the total of the array.
*/
int main()
{
  int size = 0;
  // int string_length;
  int* array = malloc(max_array_size);
  while(1){
    number_holder = get_number();
    if (number_holder == -1){
      break;
    }else if(number_holder == -2){
      continue;
    }
    if(size == max_array_size){
      printf("Array Overflow\n");
      break;
    }
    printf("%i\n",number_holder);
    array[size] = number_holder;
    size++;
  }
  printf("Size %i\n",size);
  printf("Your total is %i\n", total_array(array, size));
}
