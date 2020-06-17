#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/**
 * Name: Joshua Stone
 * Student number: 1013900
 * Course: CIS*2520
 * Date: Nov 26, 2018
 * Assignment 4
 */

/*Struct declaration*/
struct AVL_Node{
  struct AVL_Node *left, *right;
  int height;
  int frequency;
  char key[100];
};

/*prototypes*/
struct AVL_Node* insertUser(char userInsert[100], struct AVL_Node *ptr);
struct AVL_Node* delete(char ToDelete[100], struct AVL_Node *ptr);
struct AVL_Node* smallestNode(struct AVL_Node *ptr);
struct AVL_Node* rotateRight(struct AVL_Node *ptr);
struct AVL_Node* rotateLeft(struct AVL_Node *ptr);
struct AVL_Node* createAVL_Node(char thisKey[100]);
void nodeCount(struct AVL_Node *ptr);
void findALL(struct AVL_Node *ptr, int frequency);
void findKey(struct AVL_Node *ptr);
void totalCountFunction(struct AVL_Node *ptr);
int height(struct AVL_Node *ptr);
int max(int a, int b);
int returnBalance(struct AVL_Node *ptr);

/*Global variables*/
int treeSize = 0;
char keyToFind[100];
int found = 0;
int totalCount = 0;

int main(){
  int userChoice1 = 0;
  char AVLString[8] = "avl/>";
  char userInsert[100];
  struct AVL_Node *ptr = NULL;
  FILE *fp;
  char buffer[100];
  char toDelete[100];
  int initializationNum = 0;

  /*Welcome message + prompt for user input*/
  printf("Welcome to your AVL Tree\nChoose from one of the options:\n");
  do {
    printf("\nEnter a number for the option\n");
    printf("1. Initialization\n");
    printf("2. Find\n");
    printf("3. Insert\n");
    printf("4. Remove\n");
    printf("5. Check Height, Size and Total Count\n");
    printf("6. Find All (above a given frequency)\n");
    printf("7. Exit\n\n");
    printf("%s ", AVLString);
    scanf("%d", &userChoice1);

    /*Insert functionality*/
      if(userChoice1 == 3){
        if(ptr != NULL){
          printf("\nInsert key: \n\n");
          printf("%s ", AVLString);
          scanf("%s", userInsert);
          /*Just making sure the user doesn't enter a crazy long string*/
          if(strlen(userInsert) > 100){
            while(strlen(userInsert) > 100){
              printf("Error: string too long, must be less than 100\n");
              printf("Enter key again\n\n");
              printf("%s ", AVLString);
              scanf("%s", userInsert);
            }
            ptr = insertUser(userInsert, ptr);
          }
          else{
            ptr = insertUser(userInsert, ptr);
          }
        }
        else{
          printf("\nTree is empty!\n");
        }
      }
      /*Initialize the tree*/
      else if(userChoice1 == 1){
      fp = fopen("A4_data_f18.txt", "r");
        if(fp == NULL) printf("Failed to open file\n");
          else{
            if(initializationNum == 0){
              while(!feof(fp)){
                /*Scans the files one 'word' at a time, inserting each word into the tree*/
                fscanf(fp, "%s", buffer);
                ptr = insertUser(buffer, ptr);
              }
              initializationNum = 1;
            }
            else{
              printf("Already initialized\n");
            }
          }
        fclose(fp);
      }
      /*Find functionality, it prompts for a key and sees if it is in the tree*/
      else if(userChoice1 == 2){
        if(ptr == NULL) printf("\nCannot find, tree is empty!\n");
        else if(ptr != NULL){
          printf("\nFind key: \n\n%s ", AVLString);
          scanf("%s", keyToFind);
          findKey(ptr);
          if(found == 0){
            printf("\nNo_such_key\n");
            found = 0;
          }
          else if(found == 1){
            found = 0;
          }
        }
      }
      /*Removes a node from the tree*/
      else if(userChoice1 == 4){
        if(ptr == NULL) printf("\nThe tree is empty!\n");
        else if(ptr != NULL){
          printf("\nRemove key:\n\n%s ", AVLString);
          scanf("%s", toDelete);
          strcpy(keyToFind, toDelete);
          findKey(ptr);
          if(found == 0){
            printf("\nNo_such_key\n");
            found = 0;
          }
          else if(found == 1){
            delete(toDelete, ptr);
            found = 0;
          }
        }
      }
      /*Finds height, size and total count of the tree*/
      else if(userChoice1 == 5){
        treeSize = 0;
        totalCount = 0;
        /*MAKE TOTAL COUNT*/
        if(ptr == NULL) printf("\nTree is empty!\n");
        else if(ptr != NULL){
          nodeCount(ptr);
          totalCountFunction(ptr);
          printf("\nHeight: %d, Size: %d, Total Count: %d\n", ptr->height, treeSize, totalCount);
          /*Size is total nodes in the tree*/
        }
      }
      /*finds every key above a given frequency*/
      else if(userChoice1 == 6){
        if(ptr == NULL) printf("\nTree is empty!\n");
        else {
          int frequency = 0;

          printf("Frequency: \n\n");
          printf("avl/> ");
          scanf("%d", &frequency);

          printf("\n**Printing values in the tree**\n");

          findALL(ptr, frequency);
        }
        printf("\n");
      }
      /*exits the program*/
      else if(userChoice1 == 7){
        printf("\nBye!\n");
      }

  } while(userChoice1 != 7); /*while loop*/

  return 0;
}

/*inserts the given key into the tree*/
struct AVL_Node* insertUser(char userInsert[100], struct AVL_Node *ptr){
  /*Little java technique making this.key for the local function*/
  char thisKey[100];
  strcpy(thisKey, userInsert);
  int balFactor;

  if(ptr == NULL){
    return(createAVL_Node(thisKey));
  }

  if(strcmp(thisKey, ptr->key) < 0){    /*means if thisKey comes before ptr->key in the dictionary, execute*/
    ptr->left = insertUser(thisKey, ptr->left);
  }
  else if(strcmp(thisKey, ptr->key) > 0){
    ptr->right = insertUser(thisKey, ptr->right);
  }
  else{   /*case where they are equal*/
    ptr->frequency += 1;
    return ptr;
  }

  /*Grabs the height at a given time*/
  ptr->height = 1 + max(height(ptr->left), height(ptr->right));

  /*Grabs the balance of a node at a given time*/
  balFactor = returnBalance(ptr);

  /*left left case*/
  if(balFactor > 1 && strcmp(thisKey, ptr->left->key) < 0){
    return rotateRight(ptr);
  }
  /*right right case*/
  if(balFactor < -1 && strcmp(thisKey, ptr->right->key) > 0){
    return rotateLeft(ptr);
  }
  /*left right case*/
  if(balFactor > 1 && strcmp(thisKey, ptr->left->key) > 0){
    ptr->left = rotateLeft(ptr->left);
    return rotateRight(ptr);
  }
  /*right left case*/
  if(balFactor < -1 && strcmp(thisKey, ptr->right->key) < 0){
    ptr->right = rotateRight(ptr->right);
    return rotateLeft(ptr);
  }

  return ptr;
}

/*Removes a node from the tree or subtracts 1 from frequency*/
struct AVL_Node* delete(char ToDelete[100], struct AVL_Node *ptr){
  int balFactor = 0;

  if(ptr == NULL){
    return ptr;
  }

  if(strcmp(ToDelete, ptr->key) < 0){
    ptr->left = delete(ToDelete, ptr->left);
  }
  else if(strcmp(ToDelete, ptr->key) > 0){
    ptr->right = delete(ToDelete, ptr->right);
  }
  else if(strcmp(ToDelete, ptr->key) == 0){   /*case where the keys are equal, if the frequency is greater than 1, decrease by 1*/
    if(ptr->frequency > 1){
      ptr->frequency -= 1;
      return ptr;
    }
    /*Case where the node has a single child*/
    else if((ptr->left == NULL) || (ptr->right == NULL)){
      struct AVL_Node *holder = NULL;
      if(ptr->left != NULL){
        holder = ptr->left;
      }
      else{
        holder = ptr->right;
      }
      /*This happens when there are no children*/
        if(holder == NULL){
          holder = ptr;
          ptr = NULL;
        }
        else{
          *ptr = *holder;
          free(holder);
        }
     }

     /*This grabs the smaller of two children when frequency is 1, copies the data and deletes*/
     else{
     struct AVL_Node *holder = smallestNode(ptr->right);
     strcpy(ptr->key, holder->key);
     ptr->right = delete(holder->key, ptr->right);
     }
  }

  /*Similar to the insert function, we are just updating the tree, making sure its balanced*/
  ptr->height = 1 + max(height(ptr->left), height(ptr->right));

  balFactor = returnBalance(ptr);

  /*left left case*/
  if(balFactor > 1 && strcmp(ToDelete, ptr->left->key) > 0){
    return rotateRight(ptr);
  }
  /*right right case*/
  if(balFactor < -1 && strcmp(ToDelete, ptr->right->key) > 0){
    return rotateLeft(ptr);
  }
  /*left right case*/
  if(balFactor > 1 && strcmp(ToDelete, ptr->left->key) > 0){
    ptr->left = rotateLeft(ptr->left);
    return rotateRight(ptr);
  }
  /*right left case*/
  if(balFactor < -1 && strcmp(ToDelete, ptr->right->key) < 0){
    ptr->right = rotateRight(ptr->right);
    return rotateLeft(ptr);
  }

  return ptr;
}

/*Finds the furthest left most node - the smallest one*/
struct AVL_Node* smallestNode(struct AVL_Node *ptr){
  struct AVL_Node *thisNode = ptr;

  /*loop until furthest left*/
  while(thisNode->left != NULL){
    thisNode = thisNode->left;
  }

  return thisNode;
}

/*This performs a right rotation*/
struct AVL_Node* rotateRight(struct AVL_Node *ptr){
  struct AVL_Node *a = ptr->left;
  struct AVL_Node *b = a->right;

  /*switching around the nodes*/
  a->right = ptr;
  ptr->left = b;

  /*updating height*/
  ptr->height = max(height(ptr->left), height(ptr->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;

  return a;
}

/*This performs a left rotation*/
struct AVL_Node* rotateLeft(struct AVL_Node *ptr){
  struct AVL_Node *a = ptr->right;
  struct AVL_Node *b = a->left;

  /*switching around the nodes*/
  a->left = ptr;
  ptr->right = b;

  /*updating height*/
  ptr->height = max(height(ptr->left), height(ptr->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;

  return a;
}

/*Setting up the first node of the tree*/
struct AVL_Node* createAVL_Node(char thisKey[100]){
  struct AVL_Node *ptr = malloc(sizeof(struct AVL_Node));

  /*initialize all values in struct*/
  ptr->left = NULL;
  ptr->right = NULL;
  ptr->height = 1;
  ptr->frequency = 1;
  strcpy(ptr->key, thisKey);

  return (ptr);
}

/*if the node is not NULL, add 1 to size, it then goes down each left and right subtree*/
void nodeCount(struct AVL_Node *ptr){
  if(ptr != NULL){
    treeSize += 1;
  }

  if(ptr->left != NULL) nodeCount(ptr->left);
  if(ptr->right != NULL) nodeCount(ptr->right);
}

/*finds all nodes above a given Frequency*/
void findALL(struct AVL_Node *ptr, int frequency){
  if(ptr != NULL){
    if(ptr->frequency >= frequency){
      printf("Key: %s, frequency: %d\n", ptr->key, ptr->frequency);
    }

    /*go down each left and right subtree*/
    findALL(ptr->left, frequency);
    findALL(ptr->right, frequency);
  }
}

/*sees if the key is in the tree*/
void findKey(struct AVL_Node *ptr){
  if(ptr != NULL){
    /*KeyToFind is a global variable*/
    if(strcmp(keyToFind, ptr->key) != 0){
      findKey(ptr->left);
      findKey(ptr->right);
    }
    /*if strcmp returns 0, they are equal and the key is found*/
    else if(strcmp(keyToFind, ptr->key) == 0){
      printf("\nKey: %s, Frequency %d\n", ptr->key, ptr->frequency);
      found = 1;
    }
  }
}

/*Returns the total count of the tree*/
void totalCountFunction(struct AVL_Node *ptr){
  if(ptr != NULL){
    if(ptr->frequency != 0) totalCount += ptr->frequency;
  }

  /*was giving a seg fault if I didnt check before going to the left/right node*/
  if(ptr->left != NULL) totalCountFunction(ptr->left);
  if(ptr->right != NULL) totalCountFunction(ptr->right);
}

/*Simply returns the height of a node*/
int height(struct AVL_Node *ptr){
  if(ptr == NULL){
    return 0;
  }

  return ptr->height;
}

/*simply returns which is larger*/
int max(int a, int b){
  if(a > b){
    return a;
  }
  else{
    return b;
  }
}

/*simply returns the balance  of a node, using the height helper*/
int returnBalance(struct AVL_Node *ptr){
  int balance = 0;

  if(ptr == NULL){
    return 0;
  }
  else{
    balance = height(ptr->left) - height(ptr->right);
  }

  return balance;
}
