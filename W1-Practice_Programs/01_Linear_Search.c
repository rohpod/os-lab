#include <stdio.h>

int main() {
  int arr[3], i, x;
  printf("Enter 3 elements: ");
  for (i = 0; i < 3; i++) {
    scanf("%d", &arr[i]);
  }
  printf("Enter element to search: ");
  scanf("%d", &x);
  for (i = 0; i < 3; i++) {
    if (arr[i] == x) {
      printf("Element is present at index %d\n", i);
      return 0;
    }
  }
  printf("Element is not present in array\n");
  return 1;
}
