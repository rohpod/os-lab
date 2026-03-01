#include <stdio.h>

int main() {
  int arr[3], i, x;
  int low = 0, high = 2, mid;
  int found = 0;
  printf("Enter 3 elements (sorted): ");
  for (i = 0; i < 3; i++) {
    scanf("%d", &arr[i]);
  }
  printf("Enter element to search: ");
  scanf("%d", &x);
  while (low <= high) {
    mid = (low + high) / 2;
    if (arr[mid] == x) {
      printf("Element is present at index %d\n", mid);
      found = 1;
      break;
    } else if (arr[mid] < x) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  if (!found) {
    printf("Element is not present in array\n");
    return 1;
  }
  return 0;
}
