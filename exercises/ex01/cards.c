#include <stdio.h>
#include <stdlib.h>
/*
Simple Card Counting program - Software Systems
Nick Steelman
*/

/*
Will take character representing a card
If it is interpretable, will return the value, otherwise
it will return 0

card_name: char array representing card
*/
int get_number(char card_name[3]){
  int val = 0;
  switch(card_name[0]){
    case 'K':
    case 'Q':
    case 'J':
      val = 10;
      break;
    case 'A':
      val = 11;
      break;
    case 'X':
      val = 0;
      break;
    default:
      val = atoi(card_name);
      if((val < 1) || (val >10)){
        puts("I don't understand that value");
        val = 0;
      }
  }
  return val;
}

/*
Runs a loop accepting user intput representing playing cards
and increments and prints a counter according to the rules
of card counting
*/
int main(){
  char card_name[3];
  int count = 0;
  int val;
  while(card_name[0] != 'X'){
    puts("Enter the card_name: ");
    scanf("%2s", card_name);
    val = 0;
    val = get_number(card_name);
    if(val == 0){
      continue;
    }
    if((val > 2) && (val < 7)){
      count++;
    } else if (val == 10){
      count --;
    }
    printf("Current count: %i\n", count);
  }
  return 0;
}

/*
1. I only got one warnign with the flags which warned against
redeclaring int x = 0 every time. So I predeclared x and only set
it within the loop

*/
