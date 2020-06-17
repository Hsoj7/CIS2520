#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
What part you are at:
figure out why the prompt prints twice
figure out why segfault if the strings are not the same format
ex: insert: 12man, insert: man12 will seg
*/

struct AVL_Node{
  struct AVL_Node *left, *right;
  int height;
  int frequency;
  char key[10];
};

struct AVL_Node* insert(char userInsert[10], struct AVL_Node *ptr);
struct AVL_Node* rotateRight(struct AVL_Node *ptr);
struct AVL_Node* rotateLeft(struct AVL_Node *ptr);
struct AVL_Node* createAVL_Node(char thisKey[10]);
void findALL(struct AVL_Node *ptr);
int height(struct AVL_Node *ptr);
int max(int a, int b);
int getBalance(struct AVL_Node *ptr);


int main(){
  char userChoice = ' ';
  int userChoice1 = 0;
  char AVLString[8] = "avl/>";
  char userInsert[10];
  struct AVL_Node *ptr = NULL;

  printf("Welcome to your AVL Tree\nChoose from one of the options:\n");
  while(userChoice != '7'){
    printf("\nEnter a number for the option\n");
    printf("1. Initialization\n");
    printf("2. Find\n");
    printf("3. Insert\n");
    printf("4. Remove\n");
    printf("5. Check Height, Size and Total Count\n");
    printf("6. Find All (above a given frequency)\n");
    printf("7. Exit\n\n");
    printf("%s ", AVLString);
    scanf("%c", &userChoice);

    if(isalpha(userChoice)) printf("Invalid input, letter(s) found\n");
    else if(isdigit(userChoice)) userChoice1 = userChoice - '0';
    else{
      continue;
    }

    if(userChoice1 < 0 || userChoice1 > 7){
      printf("Error, number out of range\n");
      break;
    }

      if(userChoice1 == 1){

      }
      else if(userChoice1 == 2){

      }
      else if(userChoice1 == 3){
        printf("Insert key: ");
        scanf("%s", userInsert);
        if(strlen(userInsert) > 9){
          printf("Error: string too long\n");
          break;
        }
        else{
          ptr = insert(userInsert, ptr);
        }
      }
      else if(userChoice1 == 4){

      }
      else if(userChoice1 == 5){

      }
      else if(userChoice1 == 6){
        printf("\n**Printing values in the tree**\n");
        if(ptr == NULL) printf("Tree is empty!\n");
        else {
          findALL(ptr);
        }
      }
      else if(userChoice1 == 7){
        printf("\nBye!\n");
      }

  } /*while loop*/

  return 0;
}

/*inserts the given key into the tree*/
struct AVL_Node* insert(char userInsert[10], struct AVL_Node *ptr){
  /*Little java technique making this.key for the local function*/
  char thisKey[10];
  strcpy(thisKey, userInsert);
  int balFactor;

  if(ptr == NULL){
    return(createAVL_Node(thisKey));
  }

  if(strcmp(thisKey, ptr->key) < 0){    /*means if thisKey comes before ptr->key in the dictionary, execute*/
    ptr-> left = insert(thisKey, ptr->left);
  }
  else if(strcmp(thisKey, ptr->key) > 0){
    ptr->right = insert(thisKey, ptr->right);
  }
  else{   /*case where they are equal*/
    /*INCREASE COUNT IF IT IS NOT NEW*/
    return ptr; /*This line is not right*/
  }

  ptr->height = 1 + max(height(ptr->left), height(ptr->right));

  balFactor = getBalance(ptr);

  /*left left case*/
  if(balFactor > 1 && thisKey < ptr->left->key){
    return rotateRight(ptr);
  }
  /*right right case*/
  if(balFactor < -1 && thisKey > ptr->right->key){
    return rotateLeft(ptr);
  }
  /*left right case*/
  if(balFactor > 1 && thisKey > ptr->left->key){
    ptr->left = rotateLeft(ptr->left);
    return rotateRight(ptr);
  }
  /*right left case*/
  if(balFactor < -1 && thisKey < ptr->right->key){
    ptr->right = rotateRight(ptr->right);
    return rotateLeft(ptr);
  }

  return ptr;
}

struct AVL_Node* rotateRight(struct AVL_Node *ptr){
  struct AVL_Node *a = ptr->left;
  struct AVL_Node *b = a->right;

  a->right = ptr;
  ptr->left = b;

  ptr->height = max(height(ptr->left), height(ptr->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;

  return a;
}

struct AVL_Node* rotateLeft(struct AVL_Node *ptr){
  struct AVL_Node *a = ptr->right;
  struct AVL_Node *b = a->left;

  a->left = ptr;
  ptr->right = b;

  ptr->height = max(height(ptr->left), height(ptr->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;

  return a;
}

/*Setting up the first node of the tree*/
struct AVL_Node* createAVL_Node(char thisKey[10]){
  struct AVL_Node *ptr = malloc(sizeof(struct AVL_Node));

  ptr->left = NULL;
  ptr->right = NULL;
  ptr->height = 1;
  ptr->frequency = 1;
  strcpy(ptr->key, thisKey);

  return (ptr);
}

void findALL(struct AVL_Node *ptr){
  if(ptr != NULL){
    printf("%s \n", ptr->key);
    findALL(ptr->left);
    findALL(ptr->right);
  }
}

int height(struct AVL_Node *ptr){
  if(ptr == NULL){
    return 0;
  }

  return ptr->height;
}

int max(int a, int b){
  if(a > b){
    return a;
  }
  else{
    return b;
  }
}

int getBalance(struct AVL_Node *ptr){
  if(ptr == NULL){
    return 0;
  }
  else{
    return height(ptr->left) - height(ptr->right);
  }
}
