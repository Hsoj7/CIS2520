/*
Joshua Stone
Student number: 1013900
Oct 15, 2018
Assignment 2
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*declares structs and prototypes*/
struct AFR{
  char plateNum[10];
  int mileage;
  struct AFR *next; /*pointer to next node*/
};

struct rented{
  char plateNum[10];
  int mileage;
  struct rented *next;
};

void print(struct AFR *n);
struct AFR *linkAFR(struct AFR *headAFR, char mainPlateNum[10], int mainMileage);

int main(){
  FILE *fp;
  struct AFR *headAFR = NULL;
  int userChoice = 0;
  char mainPlateNum[10];
  int mainMileage = 0;
  int mainReturnDate = 0;

  /*gives headAFR some memory*/
  headAFR = malloc(sizeof(struct AFR));

  /*Opens the file to read binary*/
  fp = fopen("q1text.bin", "rb");
  fseek(fp, 0, SEEK_SET);
  /*While we havent reached the end of the file, read it and copy the values into headAFR*/
  while(!feof(fp)){
    fread(headAFR, sizeof(struct AFR), 1, fp);
    headAFR->next = NULL;
    headAFR = headAFR->next;
    headAFR = malloc(sizeof(struct AFR));
  }

  fclose(fp);

  printf("\nWelcome to your rental car assistant!\n");

  /*Loops until user wants to quit*/
  while(userChoice != 7){
    printf("Enter a transaction code (1-7):\n");
    printf("1. Add a new car to the available-for-rent list.\n2. Add a returned car to the available-for-rent list.\n3. Add a returned car to the repair list.\n4. Transfer a car from the repair list to the available-for-rent list.\n5. Rent the first availble car.\n6. Print all lists.\n7. Quit.\n");
    printf("\n>");
    scanf("%d", &userChoice);
      /*Gets user input and links it to the linked list*/
      if(userChoice == 1){
        printf("\nEnter the car's plate number\n");
        printf(">");
        scanf("%s", mainPlateNum);
        printf("\n");

        printf("Enter the car's current mileage\n>");
        scanf("%d", &mainMileage);
        printf("\n");

        headAFR = linkAFR(headAFR, mainPlateNum, mainMileage);
      }
    /*This gets the expected return date, but I did not finish :(*/
      else if(userChoice == 5){
        printf("Enter expected return date:\n>");
        scanf("%d", &mainReturnDate);
      }

      /*Prints out the AFR list*/
      else if(userChoice == 6){
        print(headAFR);
      }
      /*Quits and writes the AFR list to a file*/
      else if(userChoice == 7){
        fp = fopen("q1text.bin", "ab");
        while(headAFR != NULL){
          fwrite(headAFR, sizeof(struct AFR), 1, fp);
          headAFR = headAFR->next;
        }
        fclose(fp);
      }
  }

  printf("\nBye!\n");

  free(headAFR);
  return 0;
}

/*This puts the user values into the AFR linked list*/
struct AFR *linkAFR(struct AFR *headAFR, char mainPlateNum[10], int mainMileage){
  struct AFR *temp = malloc(sizeof(struct AFR));

  strncpy(temp->plateNum, mainPlateNum, 10);
  temp->mileage = mainMileage;
  temp->next = NULL;
  if(headAFR != NULL) temp->next = headAFR;
  headAFR = temp;
  return headAFR;
}

/*This prints out the AFR list*/
void print(struct AFR *headAFR){
  printf("\nAFR list:\n");
  while(headAFR != NULL && headAFR->mileage != 0){
    printf("Plate Number: %s\n", headAFR->plateNum);
    printf("Mileage: %d\n\n", headAFR->mileage);
    headAFR = headAFR->next;
  }
  printf("\n");

}
