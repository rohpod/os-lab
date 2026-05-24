// File Allocation Strategy: Indexed Allocation

#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_INDEX 5 /* max data blocks one index block can point to */

int disk[MAX_BLOCKS]; /* 0 = free, 1 = allocated */

void displayDisk() {
  int i;
  printf("\n%-10s %-10s\n", "Block No.", "Status");
  printf("----------------------------\n");
  for (i = 0; i < MAX_BLOCKS; i++)
    printf("%-10d %-10s\n", i, disk[i] ? "Allocated" : "Free");
}

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int i, indexBlock, numData, canAllocate;
  int indexTable[MAX_INDEX]; /* stores block numbers of data blocks */

  /* Initialize all blocks as free */
  for (i = 0; i < MAX_BLOCKS; i++)
    disk[i] = 0;

  printf("=== Indexed File Allocation ===");
  displayDisk();

  /* Step 2: Get the index block number */
  printf("\nEnter index block number: ");
  scanf("%d", &indexBlock);

  if (indexBlock < 0 || indexBlock >= MAX_BLOCKS) {
    printf("Error: Invalid block number.\n");
    return 1;
  }

  /* Step 3: Check if index block is free, then allocate it */
  if (disk[indexBlock] == 1) {
    printf("Error: Index block %d is already in use.\n", indexBlock);
    return 1;
  }
  disk[indexBlock] = 1;
  printf("Index block %d allocated.\n", indexBlock);

  /* Step 4: Get the data block numbers */
  printf("Enter number of data blocks needed: ");
  scanf("%d", &numData);

  if (numData <= 0 || numData > MAX_INDEX) {
    printf("Error: Number of data blocks must be between 1 and %d.\n",
           MAX_INDEX);
    disk[indexBlock] = 0;
    return 1;
  }

  printf("Enter the block numbers for the data blocks:\n");
  for (i = 0; i < numData; i++) {
    printf("  Data block %d: ", i + 1);
    scanf("%d", &indexTable[i]);
  }

  /* Step 5: Check if all requested data blocks are free */
  canAllocate = 1;
  for (i = 0; i < numData; i++) {
    int b = indexTable[i];
    if (b < 0 || b >= MAX_BLOCKS || b == indexBlock || disk[b] == 1) {
      printf("Error: Block %d is invalid or already allocated.\n", b);
      canAllocate = 0;
      break;
    }
  }

  /* Step 6: Allocate data blocks and store in index table */
  if (canAllocate) {
    for (i = 0; i < numData; i++)
      disk[indexTable[i]] = 1;

    printf("\nFile Allocated Successfully!\n");
    printf("Index Block : %d\n", indexBlock);
    printf("Data Blocks : ");
    for (i = 0; i < numData; i++)
      printf("%d ", indexTable[i]);
    printf("\n");
  } else {
    printf("\nAllocation Failed.\n");
    disk[indexBlock] = 0; /* rollback index block */
  }

  displayDisk();
  return 0;
}
