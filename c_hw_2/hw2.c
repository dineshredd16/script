#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct address_t	{
  int	eightBit[4];
  char alias[11];
  struct address_t*next;
};

struct address_t* insertIntoLl(struct address_t** head, int eightBit[4], char alias[11]) {
  struct address_t* newNode = (struct address_t*) malloc(sizeof(struct address_t));
  memcpy(newNode->eightBit, eightBit, sizeof(newNode->eightBit));
  strncpy(newNode->alias, alias, sizeof(newNode->alias));
  newNode->alias[sizeof(newNode->alias) - 1] = '\0';
  newNode->next = *head;
  *head = newNode;
  return *head;
}

struct address_t* splitFileString(char fileString[100], struct address_t* head){
  int eightBit[4];
  int i = 0;
  sscanf(fileString, "%d.%d.%d.%d", &eightBit[0], &eightBit[1], &eightBit[2], &eightBit[3]);
  char *space = strchr(fileString, ' ');
  char alias[100];
  strncpy(alias, space+1, sizeof(alias));
  return insertIntoLl(&head, eightBit, alias);
}

void printLinkedList(struct address_t* head){
  while (head != NULL) {
    printf("%d.%d.%d.%d %s\n", head->eightBit[0], head->eightBit[1], head->eightBit[2], head->eightBit[3], head->alias);
    head = head->next;
  }
}

int readFromFile(){
  FILE *filePtr;
  filePtr = fopen("CS531_Inet.txt", "r");
  char fileString[100];
  struct address_t* head = NULL;
  while(fgets(fileString, 100, filePtr)) {
    head = splitFileString(fileString, head);
  }
  printLinkedList(head);
  return 0;
}

void addAddress(){
  printf("addAddress");
}

void lookUpAddress(){
  printf("lookUpAddress");
}

void updateAddress(){
  printf("updateAddress");
}

void deleteAddress(){
  printf("deleteAddress");
}

void displayLl(){
  printf("displayLl");
}

void displayAliasForLocation(){
  printf("displayAliasForLocation");
}

void saveToFile(){
  printf("saveToFile");
}

int optionActions(){
  int temp=0;
  while(temp != 8){
    printf("\n\nSelect The Task With Option Number: \n\n1 --> Add address\n2 --> Look up address\n3 --> Update address\n4 --> Delete address\n5 --> Display list\n6 --> Display aliases for location\n7 --> Save to file\n8 --> Quit\n\n");
    printf("Enter Option: ");
    scanf("%d", &temp);
    switch(temp){
      case 1:
        addAddress();
        break;
      case 2:
        lookUpAddress();
        break;
      case 3:
        updateAddress();
        break;
      case 4:
        deleteAddress();
        break;
      case 5:
        displayLl();
        break;
      case 6:
        displayAliasForLocation();
        break;
      case 7:
        saveToFile();
        break;
      case 8:
        printf("\nGood Bye!");
        temp = 8;
        break;
      default:
        printf("\nPlease Try Again Invalid Input: %i", temp);
        break;
    }
  }
  return 0;
}

int main(){
  readFromFile();
  optionActions();
  return 0;
}