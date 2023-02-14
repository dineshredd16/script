#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkInputLength(char input[]){
  int len = strlen(input);
  if (len < 1 || len > 25) {
    printf("please try again, input string length should be between 1 and 25 inclusive.\n");
    return 1;
  }
  return 0;
}

int checkInvalidInput(char input[]){
  int errorCounter = 0;
  for (int j = 0; j < strlen(input); j++) {
    char temp = input[j];
    if (temp == '+' || temp == '*' || temp == '#' || temp == '$' || temp == '%' || temp == '^' || temp == '(' || temp == ')') {
      printf("Please re enter the input, %c is invalid.\n",temp);
      errorCounter++;
      break;
    }
  }
  return errorCounter;
}

int checkForCopy(char inputs[][25], int count){
  int errorCounter = 0;
  for (int j = 0; j < count; j++) {
    if (strcmp(inputs[count], inputs[j]) == 0) {
      printf("please re enter, copied string found.\n");
      errorCounter++;
      break;
    }
  }
  return errorCounter;
}

int compare_ascending(const void *a, const void *b) {
  return strcmp(*(const char**)a, *(const char**)b);
}

int compare_descending(const void *a, const void *b) {
  return strcmp(*(const char**)b, *(const char**)a);
}



int main(){
  int ascii_min = 127, ascii_max = 0;
  char min_string[25 + 1], max_string[25 + 1];
  char inputs[10][25];
  for(int i=0; i<10; i++){
    printf("enter input %d: ", i+1);
    gets(inputs[i]);
    int lengthAccepted = checkInputLength(inputs[i]);
    int inputAccepted = checkInvalidInput(inputs[i]);
    int copyAccepted = checkForCopy(inputs, i);
    if ((lengthAccepted != 0) || (inputAccepted != 0) || (copyAccepted != 0)){
        i--;
    }
     if (inputs[i][0] < ascii_min) {
        strcpy(min_string, inputs[i]);
        ascii_min = inputs[i][0];
      }
    if (inputs[i][0] > ascii_max) {
      strcpy(max_string, inputs[i]);
      ascii_max = inputs[i][0];
    }
  }

  qsort(inputs, 10, 26, compare_ascending);
  printf("Ascending order:\n");
  for (int i = 0; i < 10; i++) {
      printf("%s\n", inputs[i]);
  }
  qsort(inputs, 10, 26, compare_descending);
  printf("Descending order:\n");
  for (int i = 0; i < 10; i++) {
      printf("%s\n", inputs[i]);
  }
  printf("String with lowest ASCII value: %s\n", min_string);
  printf("String with highest ASCII value: %s\n", max_string);

  return 0;
}