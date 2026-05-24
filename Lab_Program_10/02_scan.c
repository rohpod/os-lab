// Disk Scheduling - SCAN (Elevator Algorithm)

#include <stdio.h>
#include <stdlib.h> // for abs(), qsort()

// Comparator for ascending sort
int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, head, max_cyl, dir, i;
  int total_movement = 0;

  printf("Enter number of disk requests: ");
  scanf("%d", &n);

  int req[n];
  printf("Enter the request queue: ");
  for (i = 0; i < n; i++)
    scanf("%d", &req[i]);

  printf("Enter initial head position: ");
  scanf("%d", &head);

  printf("Enter max cylinder number: ");
  scanf("%d", &max_cyl);

  printf("Enter direction (0 = towards 0, 1 = towards max): ");
  scanf("%d", &dir);

  // Sort requests in ascending order
  qsort(req, n, sizeof(int), compare);

  // Find how many requests are strictly less than head
  int left_count = 0;
  for (i = 0; i < n; i++)
    if (req[i] < head)
      left_count++;

  printf("\nOrder serviced: %d", head);

  if (dir == 0) {
    // --- Moving towards cylinder 0 first ---
    // Step 1: Service left side in descending order
    for (i = left_count - 1; i >= 0; i--) {
      total_movement += abs(head - req[i]);
      head = req[i];
      printf(" -> %d", head);
    }
    // Step 2: Go all the way to cylinder 0
    total_movement += head; // distance from last request to 0
    head = 0;
    printf(" -> 0");
    // Step 3: Reverse and service right side in ascending order
    for (i = left_count; i < n; i++) {
      total_movement += abs(head - req[i]);
      head = req[i];
      printf(" -> %d", head);
    }
  } else {
    // --- Moving towards max cylinder first ---
    // Step 1: Service right side in ascending order
    for (i = left_count; i < n; i++) {
      total_movement += abs(head - req[i]);
      head = req[i];
      printf(" -> %d", head);
    }
    // Step 2: Go all the way to max cylinder
    total_movement += abs(max_cyl - head);
    head = max_cyl;
    printf(" -> %d", max_cyl);
    // Step 3: Reverse and service left side in descending order
    for (i = left_count - 1; i >= 0; i--) {
      total_movement += abs(head - req[i]);
      head = req[i];
      printf(" -> %d", head);
    }
  }

  printf("\nTotal Head Movement: %d cylinders\n", total_movement);
  return 0;
}
