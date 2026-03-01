#include <stdio.h>

int main() {
  int arr[3], min, i, pos = 0;
  printf("Enter 3 elements: ");
  for (i = 0; i < 3; i++) {
    scanf("%d", &arr[i]);
  }
  min = arr[0];
  for (i = 1; i < 3; i++) {
    if (arr[i] < min) {
      min = arr[i];
      pos = i;
    }
  }
  printf("%d at %d\n", min, pos);
}
