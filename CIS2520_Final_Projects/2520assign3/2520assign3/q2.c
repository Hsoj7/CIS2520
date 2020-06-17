#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 20

/*Prototypes*/
void sortLeft(int heapArray[LENGTH], int k);
void sortRight(int heapArray[LENGTH], int k);
void print(int heapArray[LENGTH], int Array[20][10]);

int main(){
  FILE *fp;
  /*Max is 19 down and 9 across*/
  int Array[20][10];
  int i = 0, j = 0;
  int heapArray[LENGTH];
  int k;


  fp = fopen("f.dat", "r");

  /*Load values from f.dat into array*/
  for(i = 0; i < 20; i++){
    for(j = 0; j < 10; j++){
      fscanf(fp, " %d", &Array[i][j]);
    }
  }

  /*Initialize all keys*/
  heapArray[0] = (Array[0][0] + Array[0][1] + Array[0][2]);
  heapArray[1] = (Array[1][0] + Array[1][1] + Array[1][2]);
  heapArray[2] = (Array[2][0] + Array[2][1] + Array[2][2]);
  heapArray[3] = (Array[3][0] + Array[3][1] + Array[3][2]);
  heapArray[4] = (Array[4][0] + Array[4][1] + Array[4][2]);
  heapArray[5] = (Array[5][0] + Array[5][1] + Array[5][2]);
  heapArray[6] = (Array[6][0] + Array[6][1] + Array[6][2]);
  heapArray[7] = (Array[7][0] + Array[7][1] + Array[7][2]);
  heapArray[8] = (Array[8][0] + Array[8][1] + Array[8][2]);
  heapArray[9] = (Array[9][0] + Array[9][1] + Array[9][2]);
  heapArray[10] = (Array[10][0] + Array[10][1] + Array[10][2]);
  heapArray[11] = (Array[11][0] + Array[11][1] + Array[11][2]);
  heapArray[12] = (Array[12][0] + Array[12][1] + Array[12][2]);
  heapArray[13] = (Array[13][0] + Array[13][1] + Array[13][2]);
  heapArray[14] = (Array[14][0] + Array[14][1] + Array[14][2]);
  heapArray[15] = (Array[15][0] + Array[15][1] + Array[15][2]);
  heapArray[16] = (Array[16][0] + Array[16][1] + Array[16][2]);
  heapArray[17] = (Array[17][0] + Array[17][1] + Array[17][2]);
  heapArray[18] = (Array[18][0] + Array[18][1] + Array[18][2]);
  heapArray[19] = (Array[19][0] + Array[19][1] + Array[19][2]);


  printf("\n***SORTED***\n\n");
  /*need three passes for it to fully sort the left childs*/
  for(k = 0; k < LENGTH/2; k++){
    sortLeft(heapArray, k);
  }

  for(k = 0; k < LENGTH/2; k++){
    sortLeft(heapArray, k);
  }

  for(k = 0; k < LENGTH/2; k++){
    sortLeft(heapArray, k);
  }

  /*needs two passes to be fully sorted*/
  for(k = 0; k < LENGTH/2 - 1; k++){
    sortRight(heapArray, k);
  }

  for(k = 0; k < LENGTH/2 - 1; k++){
    sortRight(heapArray, k);
  }

  /*This function prints the 2D array according to the keys in heapArray*/
  print(heapArray, Array);
  return 0;
}

/*This function sorts the left child*/
void sortLeft(int heapArray[LENGTH], int k){
  int temp = 0;

  /*if parent is greater than left child, switch them*/
  if(heapArray[(2*k) + 1] < heapArray[k]){
    temp = heapArray[k];
    heapArray[k] = heapArray[(2*k) + 1];
    heapArray[(2*k) + 1] = temp;
  }
}

/*This function sorts the right child*/
void sortRight(int heapArray[LENGTH], int k){
  int temp = 0;

  /*if parent is greater than the right child, switch them*/
  if(heapArray[k] > heapArray[(2*k) + 2]){
    temp = heapArray[(2*k) + 2];
    heapArray[(2*k) + 2] = heapArray[k];
    heapArray[k] = temp;
  }
}

/*This function simply prints the 2D array, based on if the keys match*/
void print(int heapArray[LENGTH], int Array[20][10]){
  int i, j;

  /*loop for heapArray*/
  for(i = 0; i < LENGTH; i++){
    /*Loop for rows of 2D Array*/
    for(j = 0; j < LENGTH; j++){
        if(heapArray[i] == (Array[j][0] + Array[j][1] + Array[j][2])){
          printf("%02d %02d %02d %02d %02d %02d %02d %02d %02d %02d\n", Array[j][0], Array[j][1], Array[j][2], Array[j][3], Array[j][4], Array[j][5], Array[j][6], Array[j][7], Array[j][8], Array[j][9]);
        }
    }
  }

}
