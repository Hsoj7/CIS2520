#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*struct declaration and prototypes*/
struct expressionTree{
  char operator[10];
  struct expressionTree *leftChild;
  struct expressionTree *rightChild;
};

void display(char equation[50]);
double calculate(char equation[50]);

int main(int argc, char *argv[]){
  char equation[50];
  int userChoice = 0;
  double finalAnswer = 0;
  int k = 0;

  /*copies the command line argument into equation*/
  strcpy(equation, argv[1]);

  /*checks to see if we are dividing by 0*/
  for(k = 0; k < 50; k++){
    if(equation[k] == '/' && equation[k + 1] == '0'){
      printf("Error, divide by zero\n");
      exit(1);
    }
  }

  /*While loop to get user input*/
  while(userChoice != 7){
    printf("1. Display\n2. Preorder\n3. Inorder\n4. PostOrder\n5. Update\n6. Calculate\n7. Exit\n\n");
    printf(">");
    scanf("%d", &userChoice);

    /*Displays the equation*/
    if(userChoice == 1){
      display(equation);
    }

    if(userChoice == 2){

    }

    /*Prints the equation*/
    if(userChoice == 3){
      printf("\n%s\n\n", equation);
    }

    if(userChoice == 4){

    }

    if(userChoice == 5){

    }

    /*calculates the equation*/
    if(userChoice == 6){
      finalAnswer = calculate(equation);
      printf("\nFinal Answer = %.2f\n\n", finalAnswer);
    }
  }

  return 0;
}

/*This guy prints the equation*/
void display(char equation[50]){
  printf("\nEquation = %s\n\n", equation);
}

/*This function calculates the given equation. Doesn't fully work*/
double calculate(char equation[50]){
  double total = 0.0;
  double tempArr[10];
  int i = 0, k = 0;
  int length = strlen(equation);
  int openBrackCount = 0, closedBrackCount = 0;
  char operatorStack[10];

  /*initializes each value in the operator stack to be 0*/
  for(k = 0; k < 10; k ++){
    operatorStack[k] = '0';
  }

  /*Initializes every value in the tempArr array to 0*/
  for(k = 0; k < 10; k++){
    tempArr[k] = 0.000000;
  }

  for(i = 0; i < length; i++){
    /*checks to see if the current character is an open bracket*/
    if(equation[i] == '('){
      openBrackCount += 1;
    }
    /*checks to see if the current character is a closed bracket*/
    else if(equation[i] == ')'){
      closedBrackCount += 1;
    }
    /*checks to see if it is a deciaml number in the form #.##*/
    else if(isdigit(equation[i]) && equation[i + 1] == '.' && isdigit(equation[i + 2]) && isdigit(equation[i + 3])){
      for(k = 0; k < 10; k++){
        if(tempArr[k] == 0.000000){
          tempArr[k] = tempArr[k] + (equation[i] - '0');
          tempArr[k] = tempArr[k] + (equation[i + 2] - '0') / 10.0;
          tempArr[k] = tempArr[k] + (equation[i + 3] - '0') / 100.0;
          printf("tempArr = %f\n", tempArr[k]);
          break;
        }
      }

    }
    /*Put here the check for a variable*/

    /*checks if the current character is an operator*/
    else if(equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/'){
      for(k = 0; k < 10; k++){
        if(operatorStack[k] == '0'){
          operatorStack[k] = equation[i];
          printf("operatorStack = %c\n", operatorStack[k]);
          break;
        }
      }
    }

    /*if the operator stack contains a +, -, / or *, compute what is in tempArr and store it in the final total*/
    for(k = 0; k < 10; k++){
      if(operatorStack[k] == '+' && tempArr[0] != 0 && tempArr[1] != 0){
        total = total + (tempArr[0] + tempArr[1]);
        operatorStack[k] = '0';
        tempArr[0] = total;
        tempArr[1] = 0.0;
      }
      else if(operatorStack[k] == '-' && tempArr[0] != 0 && tempArr[1] != 0){
        total = total + (tempArr[0] - tempArr[1]);
        operatorStack[k] = '0';
        tempArr[0] = total;
        tempArr[1] = 0.0;
      }
      else if(operatorStack[k] == '*' && tempArr[0] != 0 && tempArr[1] != 0){
        total = total + (tempArr[0] * tempArr[1]);
        operatorStack[k] = '0';
        tempArr[0] = total;
        tempArr[1] = 0.0;
      }
      else if(operatorStack[k] == '/' && tempArr[0] != 0 && tempArr[1] != 0){
        total = total + (tempArr[0] / tempArr[1]);
        operatorStack[k] = '0';
        tempArr[0] = total;
        tempArr[1] = 0.0;
      }
    }

  }

  printf("local total = %f\n", total);
  return total;
}
