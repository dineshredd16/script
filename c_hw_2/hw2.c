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
  int count = 0;
  while (head != NULL) {
    printf("%d.%d.%d.%d %s\n", head->eightBit[0], head->eightBit[1], head->eightBit[2], head->eightBit[3], head->alias);
    head = head->next;
    count++;
  }
  printf("Total Node Count: %d", count);
}

int searchAlias(struct address_t* head, char* alias) {
  struct address_t* present = head;
  while (present != NULL) {
    if (strcmp(present->alias, alias) == 0) {
      return 1;
    }
    present = present->next;
  }
  return 0;
}

struct address_t* readFromFile(){
  FILE *filePtr;
  filePtr = fopen("CS531_Inet.txt", "r");
  char fileString[100];
  struct address_t* head = NULL;
  while(fgets(fileString, 100, filePtr)) {
    head = splitFileString(fileString, head);
  }
  printLinkedList(head);
  printf("\ninitial read of all the data records from CS531_Inet.txt is completed.");
  return head;
}

void addAddress(struct address_t* head){
  char str;
  char address[100];
  printf("\nAdding Address: \n");
  printf("\nEnter Alias: ");
  scanf("%s", &str);
  if (searchAlias(head, &str) == 1) {
    printf("error: %d already exists in the linked list!\n", str);
  } 
  else {
    printf("Enter Address For %c", str);
    scanf("%s", address);
    splitFileString(address, head);
  }
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

void displayLl(struct address_t* head){
  printf("\nDisplaying the list: \n\n");
  printLinkedList(head);
}

void displayAliasForLocation(){
  printf("displayAliasForLocation");
}

void saveToFile(){
  printf("saveToFile");
}

int optionActions(struct address_t* head){
  int temp=0;
  while(temp != 8){
    printf("\n\nSelect The Task With Option Number: \n\n1 --> Add address\n2 --> Look up address\n3 --> Update address\n4 --> Delete address\n5 --> Display list\n6 --> Display aliases for location\n7 --> Save to file\n8 --> Quit\n\n");
    printf("Enter Option: ");
    scanf("%d", &temp);
    switch(temp){
      case 1:
        addAddress(head);
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
        displayLl(head);
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
  optionActions(readFromFile());
  return 0;
}