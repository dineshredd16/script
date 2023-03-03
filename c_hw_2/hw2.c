#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct address_t	{
  int	eightBit[4];
  char alias[11];
  struct address_t*next;
};

int insertIntoLl(struct address_t** head, int eightBit[4], char alias[11]) {
  struct address_t* newNode = (struct address_t*) malloc(sizeof(struct address_t));
  memcpy(newNode->eightBit, eightBit, sizeof(newNode->eightBit));
  strncpy(newNode->alias, alias, sizeof(newNode->alias));
  newNode->alias[sizeof(newNode->alias) - 1] = '\0';
  newNode->next = *head;
  *head = newNode;
  return 0;
}

int splitFileString(char fileString[100], struct address_t* head){
  int eightBit[4];
  int i = 0;
  sscanf(fileString, "%d.%d.%d.%d", &eightBit[0], &eightBit[1], &eightBit[2], &eightBit[3]);
  char *space = strchr(fileString, ' ');
  char alias[100];
  strncpy(alias, space+1, sizeof(alias));
  insertIntoLl(&head, eightBit, alias);
  return 0;
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
    splitFileString(fileString, head);
  }
  printLinkedList(head);
  return 0;
}

int main(){
  readFromFile();
  return 0;
}