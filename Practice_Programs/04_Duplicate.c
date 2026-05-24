#include <stdio.h>

int main() {
  int arr[3], i, j;
  printf("Enter 3 elements: ");
  for (i = 0; i < 3; i++) {
    scanf("%d", &arr[i]);
  }
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      if (i != j && arr[i] == arr[j]) {
        printf("Duplicate\n");
        return 0;
      }
  printf("No Duplicates\n");
  return 0;
}
