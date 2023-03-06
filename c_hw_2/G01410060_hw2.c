#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct address_t	{
  int	eightBit[4];
  char alias[11];
  struct address_t *next;
};

struct address_t *head = NULL;

void  insertIntoLl(int first, int second, int third, int fourth, char alias[11]) {
  struct address_t *temp_address = (struct address_t*)malloc(sizeof(struct address_t));
	temp_address->eightBit[0] = first;
	temp_address->eightBit[1] = second;
	temp_address->eightBit[2] = third;
	temp_address->eightBit[3] = fourth;
	strcpy(temp_address->alias,alias);
	temp_address->next = NULL;
	if(head==NULL){
		head = temp_address;
		head->next = NULL;
		return;
	}
	struct address_t* tail = NULL;
	tail = head;
	while(tail->next!=NULL){
		tail = tail->next;
	}
	tail->next = temp_address;
	return;
}

void printLinkedList(){
  int count = 0;
  struct address_t *temp = NULL;
  temp = head;
  if(temp == NULL){
    printf("\n ----- Error: No Addresses Found -----");
  }
  while (temp != NULL) {
    printf("%d.%d.%d.%d %s\n", temp->eightBit[0], temp->eightBit[1], temp->eightBit[2], temp->eightBit[3], temp->alias);
    temp = temp->next;
    count++;
  }
  printf("Total Node Count: %d", count);
}

int searchAndValidateAlias(char alias[11]) {
  struct address_t* present = head;
  while (present != NULL) {
    if ((strcmp(present->alias, alias) == 0) || (strlen(alias) > 10)){
      return 1;
    }
    present = present->next;
  }
  return 0;
}

int searchAndValidateEightBit(int eightBit[4]){
  struct address_t* present = head;
  while (present != NULL) {
    if ((present->eightBit[0] == eightBit[0] && present->eightBit[1] == eightBit[1] && present->eightBit[2] == eightBit[2] && present->eightBit[3] == eightBit[3]) || (eightBit[0] > 255 || eightBit[0] < 0 || eightBit[1] > 255 || eightBit[1] < 0 || eightBit[2] > 255 || eightBit[2] < 0 || eightBit[3] > 255 || eightBit[4] < 0)){
      return 1;
    }
    present = present->next;
  }
  return 0;
}

void insertFromFile(){
  FILE *filePtr;
  filePtr = fopen("CS531_Inet.txt", "r");
  char fileString[100];
  while(fgets(fileString, 100, filePtr)) {
    int eightBit[4];
    char alias[11];
    sscanf(fileString, "%d.%d.%d.%d %s", &eightBit[0], &eightBit[1], &eightBit[2], &eightBit[3], alias);
    insertIntoLl(eightBit[0], eightBit[1], eightBit[2], eightBit[3], alias);
  }
  printf("\ninitial read of all the data records from CS531_Inet.txt is completed.");
}

void addAddress(){
  int z=0;
  char str[100];
  char address[100];
  printf("\nEnter Alias: ");
  scanf("%s", str);
  while (searchAndValidateAlias(str) == 1) {
    printf("Error: %s is already present in the linked list or the alias lenght is above 10 charatcers. \n Please Re- Enter: ", str);
    scanf("%s", str);
    break;
  }
  printf("\nEnter Address For %s: ", str);
  scanf("%s", address);
  int temp=0;
  for (int count = 0; address[count] != '\0'; count++){
    if (strcmp(&address[count], ".") == 0){
      temp++;
    }
  }
  if (temp == 3){
    int eightBit[4];
    sscanf(address, "%d.%d.%d.%d", &eightBit[0], &eightBit[1], &eightBit[2], &eightBit[3]);
    while (searchAndValidateEightBit(eightBit) == 1) {
      printf("Error: %d.%d.%d.%d is already present in the linked list or the address is not with the range of 0 to 255. \n Please Re- Enter: ", eightBit[0], eightBit[1], eightBit[2], eightBit[3]);
      scanf("%s", address);
      sscanf(address, "%d.%d.%d.%d", &eightBit[0], &eightBit[1], &eightBit[2], &eightBit[3]);
      z=1;
      break;
    }
    if (z ==0){
      insertIntoLl(eightBit[0], eightBit[1], eightBit[2], eightBit[3], str);
      printf("Address - %d.%d.%d.%d added succesfully For - %s", eightBit[0], eightBit[1], eightBit[2], eightBit[3], str);
    }
  }
  else {
    printf("Invalid Address");
    return;
  }
}

int lookUpAddress(char str[100]){
  int i=0;
  struct address_t* present = head;
  while (present != NULL) {
    if ((strcmp(present->alias, str) == 0)){
      printf("Address for %s: %d.%d.%d.%d", str, present->eightBit[0], present->eightBit[1], present->eightBit[2], present->eightBit[3]);
      i = 1;
      return 1;
    }
    present = present->next;
  }
  if (i == 0){
    printf("error: %s does not exists", str);
    return 0;
  }
  return 0;
}

void updateAddress(char str[100]){
  if (lookUpAddress(str) == 0){
    printf("Alias %s Not Found", str);
    return;
  }
  int input[4];
  int flag=0;
  for(int i=0; i<4; i++){
    printf("\n\n Enter Value #%d (0-255): ", i+1);
    scanf("%d", &input[i]);
    while(input[i] > 255 || input[i] < 0){
      printf("Error: %d is illegal. \n Please Re- Enter: ", input[i]);
      scanf("%d", &input[i]);
    }
  }
  if (searchAndValidateEightBit(input) == 1){
    printf("error: ipv4 already exists.");
    return;
  }
  struct address_t* current = head;
  while (current != NULL) {
    if (strcmp(current->alias,str) == 0) {
      for(int j=0; j<4; j++){
        current->eightBit[j] = input[j];
      }
      printf("update Succesfull for %s, new ipv4 address: %d.%d.%d.%d", str, input[0], input[1], input[2], input[3]);
      break;
    }
    current = current->next;
  }
  return;
}

void deleteAddress(){
  char str[100];
  int i=0;
  printf("\nEnter Alias: ");
  scanf("%s", str);
  if (head != NULL && strcmp(head->alias,str)==0) {
    struct address_t* temp = head;
    head = head->next;
    free(temp);
    return;
  }
  struct address_t* current = head;
  while (current != NULL && current->next != NULL) {
    if (strcmp(current->next->alias,str) == 0){
      char answer[2];
      printf("Delete %s-%d.%d.%d.%d?	(y/n)", str, current->next->eightBit[0], current->next->eightBit[1], current->next->eightBit[2], current->next->eightBit[3]);
      scanf("%s", answer);
      if (strcmp(answer, "y") == 0){
        struct address_t* temp = current->next;
        current->next = current->next->next;
        free(temp);
        printf("%s Deleted Succesfully", str);
        i = 1;
        return;
      }
      else{
        printf("Delete Action Aborted");
        return;
      }
    }
    current = current->next;
  }
  if (i == 0) {
    printf("error: %s Not Found", str);
  }
}

void displayLl(){
  printf("\n----- Displaying the list -----\n");
  printLinkedList();
}

void displayAliasForLocation(){
  int input[2];
  int flag=0;
  for(int i=0; i<2; i++){
    printf("\n\n Enter Location Value #%d (0-255): ", i+1);
    scanf("%d", &input[i]);
    while(input[i] > 255 || input[i] < 0){
      printf("Error: %d is illegal. \n Please Re- Enter: ", input[i]);
      scanf("%d", &input[i]);
    }
  }
  struct address_t *temp = head;
  while(temp!=NULL){
		if(temp->eightBit[0]==input[0] && temp->eightBit[1] == input[1]){
			flag = 1;
			printf("%d.%d.%d.%d - %s\n",temp->eightBit[0],temp->eightBit[1],temp->eightBit[2],temp->eightBit[3],temp->alias);
		}
		temp = temp->next;
	}
  if (flag == 0) {
    printf("The Location Does not exist on the list");
  }
}

void saveToFile(){
  char fileName[100];
	printf("\nEnter .txt file name: ");
	scanf("%123s",fileName);
	strcat(fileName,".txt");
	FILE *file;
	file=fopen(fileName,"w");
  struct address_t *temp = head;
   while(temp!=NULL){
    fprintf(file, "%d.%d.%d.%d %s\n",temp->eightBit[0],temp->eightBit[1],temp->eightBit[2],temp->eightBit[3],temp->alias);
    temp = temp->next;
	}
	printf("\nsuccesfully created file with all entries\n");
  fclose(file);
}

int optionActions(){
  int temp=0;
  while(temp != 8){
    char str[100];
    printf("\n\nSelect The Task With Option Number: \n\n1 --> Add address\n2 --> Look up address\n3 --> Update address\n4 --> Delete address\n5 --> Display list\n6 --> Display aliases for location\n7 --> Save to file\n8 --> Quit\n\n");
    printf("Enter Option: ");
    scanf("%d", &temp);
    switch(temp){
      if (temp == 1 || temp == 2 || temp == 3 || temp == 4 || temp == 5 || temp == 6 || temp == 7 || temp == 8){
        case 1:
          addAddress();
          break;
        case 2:
          printf("\nEnter Alias: ");
          scanf("%s", str);
          lookUpAddress(str);
          break;
        case 3:
          printf("\nEnter Alias: ");
          scanf("%s", str);
          updateAddress(str);
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
      else {
        printf("\nPlease Try Again Invalid Input: %i", temp);
        break;
        return 0;
      }
    }
  }
  return 0;
}

int main(){
  insertFromFile();
  optionActions();
}