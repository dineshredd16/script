#include <stdio.h>
#include <string.h>

#define MAX_LEN 25
#define NUM_STRINGS 10

int compare_strings(const void *a, const void *b) {
  const char *str1 = (const char *)a;
  const char *str2 = (const char *)b;
  return strcmp(str1, str2);
}

int main(void) {
  char strings[NUM_STRINGS][MAX_LEN + 1];
  int i, j, len, order = 0, ascii_min = 127, ascii_max = 0;
  char min_string[MAX_LEN + 1], max_string[MAX_LEN + 1];

  // Prompt for and read in the strings
  for (i = 0; i < NUM_STRINGS; i++) {
    printf("Enter string %d (1-25 characters): ", i + 1);
    gets(strings[i]);

    // Check length
    len = strlen(strings[i]);
    if (len < 1 || len > MAX_LEN) {
      printf("Error: string length must be between 1 and 25 inclusive.\n");
      i--;
      continue;
    }

    // Check for invalid characters
    for (j = 0; j < len; j++) {
      char c = strings[i][j];
      if (c == '+' || c == '*' || c == '#' || c == '$' || c == '%' || c == '^' || c == '(' || c == ')') {
        printf("Error:%c is an illegal character-please re-enter.\n",c);
        i--;
        goto next_string;
      }
    }

    // Check for duplicates
    for (j = 0; j < i; j++) {
      if (strcmp(strings[i], strings[j]) == 0) {
        printf("Error: duplicate string.- please re-enter\n");
        i--;
        goto next_string;
      }
    }

    // Determine min and max ASCII value
    if (strings[i][0] < ascii_min) {
      strcpy(min_string, strings[i]);
      ascii_min = strings[i][0];
    }
    if (strings[i][0] > ascii_max) {
      strcpy(max_string, strings[i]);
      ascii_max = strings[i][0];
    }

    next_string:
    continue;
  }

  // Prompt for sort order
  printf("Sort in ascending (A) or descending (D) order? ");
  char sort_order[2];
  scanf("%s", sort_order);
  if (strcmp(sort_order, "A") == 0) {
    order = 1;
  } else if (strcmp(sort_order, "D") == 0) {
    order = -1;
  } else {
    printf("Error: invalid sort order.\n");
    return 1;
  }

  // Sort the strings
  qsort(strings, NUM_STRINGS,MAX_LEN + 1, compare_strings);

// Print the sorted strings
printf("Sorted strings:\n");
for (i = 0; i < NUM_STRINGS; i++) {
printf("%s\n", strings[i]);
}

// Print the string with the lowest ASCII value
printf("String with lowest ASCII value: %s\n", min_string);

// Print the string with the highest ASCII value
printf("String with highest ASCII value: %s\n", max_string);

return 0;
}


