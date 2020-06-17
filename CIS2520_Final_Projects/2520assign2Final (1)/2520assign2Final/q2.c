/*
Joshua Stone
Student number: 1013900
Oct 15, 2018
Assignment 2
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Delcaring variables and prototypes*/
int stackArray[50];
int topOfArray = -1;

int calculate(char *equation);
void put(int x);
int take();

/*Needed to use argc and argv for the command line input*/
int main(int argc, char *argv[]){
  char *equation;
  int total = 0;

  /*Sets the local varibale equation to the user input*/
  equation = argv[1];
  total = calculate(equation);
  printf("Total = %d\n", total);

  return 0;
}

/*This function calculates the given equation*/
int calculate(char *equation){
  int i;
  int calc1 = 0, calc2 = 0, total = 0 , length = 0;
  length = strlen(equation);

  for(i = 0; i < length; ++i){
    /*checking to see if its a number or arithmatic operator*/
    if(isdigit(equation[i])){
      /*It gives the ascii value, so we need to subtract 48 to get decimal value*/
      put(equation[i] - 48);
    }
    else{
      /*takes the top two numbers on the stack*/
      calc1 = take();
      calc2 = take();
      /*All of these do the respective calculation*/
      if(equation[i] == '+'){
        total = calc1 + calc2;
      }
      else if(equation[i] == '-'){
        total = calc2 - calc1;
      }
      else if(equation[i] == '*'){
        total = calc1 * calc2;
      }
      else if(equation[i] == '/'){
        total = calc1 / calc2;
      }
      /*once calculated, it puts the total on the stack for the next operation*/
      put(total);
    }
  }
  return total;
}

/*puts the given number on the top of the stack*/
void put(int total){
  stackArray[++topOfArray] = total;
}

/*Takes the top number from the stack*/
int take(){
  return stackArray[topOfArray--];
}
