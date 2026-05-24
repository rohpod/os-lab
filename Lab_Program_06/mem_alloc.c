// Lab Program 6: Memory Allocation Techniques

#include <stdio.h>

void firstFit(int blocks[], int m, int processes[], int n) {
  int alloc[n], used[m];
  for (int i = 0; i < m; i++)
    used[i] = 0;
  for (int i = 0; i < n; i++)
    alloc[i] = -1;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (!used[j] && blocks[j] >= processes[i]) {
        alloc[i] = j;
        used[j] = 1;
        break;
      }

  printf("\n--- First Fit ---\n");
  printf("Process No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t", i + 1, processes[i]);
    if (alloc[i] != -1)
      printf("%d\n", alloc[i] + 1);
    else
      printf("Not Allocated\n");
  }
}

void bestFit(int blocks[], int m, int processes[], int n) {
  int alloc[n], used[m];
  for (int i = 0; i < m; i++)
    used[i] = 0;
  for (int i = 0; i < n; i++)
    alloc[i] = -1;

  for (int i = 0; i < n; i++) {
    int best = -1;
    for (int j = 0; j < m; j++)
      if (!used[j] && blocks[j] >= processes[i])
        if (best == -1 || blocks[j] < blocks[best])
          best = j;
    if (best != -1) {
      alloc[i] = best;
      used[best] = 1;
    }
  }

  printf("\n--- Best Fit ---\n");
  printf("Process No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t", i + 1, processes[i]);
    if (alloc[i] != -1)
      printf("%d\n", alloc[i] + 1);
    else
      printf("Not Allocated\n");
  }
}

void worstFit(int blocks[], int m, int processes[], int n) {
  int alloc[n], used[m];
  for (int i = 0; i < m; i++)
    used[i] = 0;
  for (int i = 0; i < n; i++)
    alloc[i] = -1;

  for (int i = 0; i < n; i++) {
    int worst = -1;
    for (int j = 0; j < m; j++)
      if (!used[j] && blocks[j] >= processes[i])
        if (worst == -1 || blocks[j] > blocks[worst])
          worst = j;
    if (worst != -1) {
      alloc[i] = worst;
      used[worst] = 1;
    }
  }

  printf("\n--- Worst Fit ---\n");
  printf("Process No.\tProcess Size\tBlock No.\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t", i + 1, processes[i]);
    if (alloc[i] != -1)
      printf("%d\n", alloc[i] + 1);
    else
      printf("Not Allocated\n");
  }
}

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int m, n;

  printf("Enter number of memory blocks: ");
  scanf("%d", &m);
  int blocks[m];
  printf("Enter sizes of %d memory blocks:\n", m);
  for (int i = 0; i < m; i++)
    scanf("%d", &blocks[i]);

  printf("Enter number of processes: ");
  scanf("%d", &n);
  int processes[n];
  printf("Enter sizes of %d processes:\n", n);
  for (int i = 0; i < n; i++)
    scanf("%d", &processes[i]);

  firstFit(blocks, m, processes, n);
  bestFit(blocks, m, processes, n);
  worstFit(blocks, m, processes, n);

  return 0;
}
