// Deadlock Detection - Several Instances Banker's Algorithm

#include <stdio.h>

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, m;

  printf("Enter the number of processes: ");
  scanf("%d", &n);
  printf("Enter the number of resources: ");
  scanf("%d", &m);

  int alloc[n][m], request[n][m], avail[m];
  int finish[n], safeSeq[n];

  // Input Allocation Matrix
  printf("Enter the allocation matrix:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: ", i);
    for (int j = 0; j < m; j++)
      scanf("%d", &alloc[i][j]);
  }

  // Input Request Matrix
  printf("Enter the request matrix:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: ", i);
    for (int j = 0; j < m; j++)
      scanf("%d", &request[i][j]);
  }

  // Input Available Resources
  printf("Enter the available resources: ");
  for (int j = 0; j < m; j++)
    scanf("%d", &avail[j]);

  // Step 1(a): Work = Available
  int work[m];
  for (int j = 0; j < m; j++)
    work[j] = avail[j];

  // Step 1(b): If Allocation[i] != 0, Finish[i] = false, else true
  for (int i = 0; i < n; i++) {
    int hasAlloc = 0;
    for (int j = 0; j < m; j++) {
      if (alloc[i][j] != 0) {
        hasAlloc = 1;
        break;
      }
    }
    finish[i] = hasAlloc ? 0 : 1; // 0 = false, 1 = true
  }

  // Step 2 & 3: Detection Algorithm
  int count = 0;
  while (count < n) {
    int found = 0;
    for (int i = 0; i < n; i++) {
      if (finish[i] == 0) {
        // Check if Request[i] <= Work
        int canRun = 1;
        for (int j = 0; j < m; j++) {
          if (request[i][j] > work[j]) {
            canRun = 0;
            break;
          }
        }
        // Step 3: Release resources, mark finished
        if (canRun) {
          for (int j = 0; j < m; j++)
            work[j] += alloc[i][j];
          finish[i] = 1;
          safeSeq[count++] = i;
          found = 1;
        }
      }
    }
    if (!found)
      break;
  }

  // Step 4: Check for deadlock
  int deadlock = 0;
  for (int i = 0; i < n; i++) {
    if (finish[i] == 0) {
      deadlock = 1;
      break;
    }
  }

  if (!deadlock) {
    printf("System is in safe state.\n");
    printf("Safe Sequence is: ");
    for (int i = 0; i < count; i++)
      printf("P%d ", safeSeq[i]);
    printf("\n");
  } else {
    printf("System is NOT in safe state. Deadlock detected!\n");
    printf("Deadlocked processes: ");
    for (int i = 0; i < n; i++)
      if (finish[i] == 0)
        printf("P%d ", i);
    printf("\n");
  }

  return 0;
}
