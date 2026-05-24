// Deadlock Avoidance using Banker's Algorithm

#include <stdio.h>

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, m;

  printf("Enter number of processes: ");
  scanf("%d", &n);
  printf("Enter number of resources: ");
  scanf("%d", &m);

  int alloc[n][m], max[n][m], avail[m];
  int need[n][m], finish[n], safeSeq[n];

  // Input Allocation Matrix
  printf("Enter Allocation Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &alloc[i][j]);

  // Input Maximum Demand Matrix
  printf("Enter Maximum Demand Matrix:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      scanf("%d", &max[i][j]);

  // Input Available Resources
  printf("Enter Available Resources:\n");
  for (int j = 0; j < m; j++)
    scanf("%d", &avail[j]);

  // Step 1: Calculate Need and initialize Finish
  for (int i = 0; i < n; i++) {
    finish[i] = 0; // false
    for (int j = 0; j < m; j++)
      need[i][j] = max[i][j] - alloc[i][j];
  }

  // Work = Available
  int work[m];
  for (int j = 0; j < m; j++)
    work[j] = avail[j];

  // Step 2 & 3: Safety Algorithm
  int count = 0;
  while (count < n) {
    int found = 0;
    for (int i = 0; i < n; i++) {
      if (finish[i] == 0) {
        // Check if Need[i] <= Work
        int canRun = 1;
        for (int j = 0; j < m; j++) {
          if (need[i][j] > work[j]) {
            canRun = 0;
            break;
          }
        }
        // Step 3: Allocate resources and mark finished
        if (canRun) {
          for (int j = 0; j < m; j++)
            work[j] += alloc[i][j];
          finish[i] = 1; // true
          safeSeq[count++] = i;
          found = 1;
        }
      }
    }
    if (!found)
      break; // No process found, not safe
  }

  // Step 4: Check if all finished
  if (count == n) {
    printf("\nSystem is in a safe state.\n");
    printf("Safe sequence is: ");
    for (int i = 0; i < n; i++) {
      printf("P%d", safeSeq[i]);
      if (i != n - 1)
        printf(" -> ");
    }
    printf("\n");
  } else {
    printf("\nSystem is NOT in a safe state.\n");
  }

  return 0;
}
