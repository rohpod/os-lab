// Disk Scheduling - C-LOOK (Circular LOOK)

#include <stdio.h>
#include <stdlib.h> // for abs(), qsort()

// Comparator for ascending sort
int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, head, i;
  int total_movement = 0;

  printf("Enter number of disk requests: ");
  scanf("%d", &n);

  int req[n];
  printf("Enter the request queue: ");
  for (i = 0; i < n; i++)
    scanf("%d", &req[i]);

  printf("Enter initial head position: ");
  scanf("%d", &head);

  // Sort requests in ascending order
  qsort(req, n, sizeof(int), compare);

  // Split into left (< head) and right (>= head)
  int left_count = 0;
  for (i = 0; i < n; i++)
    if (req[i] < head)
      left_count++;

  printf("\nOrder serviced: %d", head);

  // Step 1: Service right list in ascending order (up to highest request)
  for (i = left_count; i < n; i++) {
    total_movement += abs(head - req[i]);
    head = req[i];
    printf(" -> %d", head);
  }

  // Step 2: Jump directly to the lowest request in the left list
  //         (no trip to disk end — this is the C-LOOK distinction)
  if (left_count > 0) {
    total_movement += abs(head - req[0]); // jump distance
    head = req[0];
    printf(" -> %d", head);

    // Step 3: Service left list in ascending order
    for (i = 1; i < left_count; i++) {
      total_movement += abs(head - req[i]);
      head = req[i];
      printf(" -> %d", head);
    }
  }

  printf("\nTotal Head Movement: %d cylinders\n", total_movement);
  return 0;
}
