// Page Frame Replacement Techniques

#include <stdbool.h>
#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

bool isPresent(int frames[], int n, int page) {
  for (int i = 0; i < n; i++)
    if (frames[i] == page)
      return true;
  return false;
}

//  Print summary: hits, misses, percentages
void printSummary(const char *algo, int n, int misses) {
  int hits = n - misses;
  printf("\n[%s Summary]\n", algo);
  printf("Total Accesses : %d\n", n);
  printf("Total Hits     : %d\n", hits);
  printf("Total Misses   : %d\n", misses);
  printf("Hit/Miss Ratio : %.2f%%\n", (hits * 100.0) / misses);
}

//  FIFO Page Replacement
void fifo(int pages[], int n, int numFrames) {
  int frames[MAX_FRAMES];
  int misses = 0, pointer = 0;

  for (int i = 0; i < numFrames; i++)
    frames[i] = -1;

  printf("\n--- FIFO ---\n");
  printf("%-5s | Frames\n", "Page");

  for (int i = 0; i < n; i++) {
    printf("%-5d | ", pages[i]);

    if (!isPresent(frames, numFrames, pages[i])) {
      frames[pointer] = pages[i];
      pointer = (pointer + 1) % numFrames;
      misses++;
      for (int j = 0; j < numFrames; j++)
        (frames[j] == -1) ? printf("- ") : printf("%d ", frames[j]);
      printf(" *MISS*");
    } else {
      for (int j = 0; j < numFrames; j++)
        (frames[j] == -1) ? printf("- ") : printf("%d ", frames[j]);
      printf(" *HIT*");
    }
    printf("\n");
  }
  printSummary("FIFO", n, misses);
}

//  LRU Page Replacement
void lru(int pages[], int n, int numFrames) {
  int frames[MAX_FRAMES];
  int lastUsed[MAX_FRAMES];
  int misses = 0;

  for (int i = 0; i < numFrames; i++) {
    frames[i] = -1;
    lastUsed[i] = 0;
  }

  printf("\n--- LRU ---\n");
  printf("%-5s | Frames\n", "Page");

  for (int i = 0; i < n; i++) {
    printf("%-5d | ", pages[i]);

    if (!isPresent(frames, numFrames, pages[i])) {
      int lruIdx = 0;
      for (int j = 1; j < numFrames; j++)
        if (lastUsed[j] < lastUsed[lruIdx])
          lruIdx = j;

      frames[lruIdx] = pages[i];
      lastUsed[lruIdx] = i + 1;
      misses++;

      for (int j = 0; j < numFrames; j++)
        (frames[j] == -1) ? printf("- ") : printf("%d ", frames[j]);
      printf(" *MISS*");
    } else {
      for (int j = 0; j < numFrames; j++)
        if (frames[j] == pages[i]) {
          lastUsed[j] = i + 1;
          break;
        }

      for (int j = 0; j < numFrames; j++)
        (frames[j] == -1) ? printf("- ") : printf("%d ", frames[j]);
      printf(" *HIT*");
    }
    printf("\n");
  }
  printSummary("LRU", n, misses);
}

//  Optimal Page Replacement
int findOptimalVictim(int frames[], int numFrames, int pages[], int n,
                      int current) {
  int farthest = -1, victimIdx = 0;

  for (int i = 0; i < numFrames; i++) {
    int nextUse = n;
    for (int j = current + 1; j < n; j++) {
      if (pages[j] == frames[i]) {
        nextUse = j;
        break;
      }
    }
    if (nextUse > farthest) {
      farthest = nextUse;
      victimIdx = i;
    }
  }
  return victimIdx;
}

void optimal(int pages[], int n, int numFrames) {
  int frames[MAX_FRAMES];
  int misses = 0, filled = 0;

  for (int i = 0; i < numFrames; i++)
    frames[i] = -1;

  printf("\n--- Optimal ---\n");
  printf("%-5s | Frames\n", "Page");

  for (int i = 0; i < n; i++) {
    printf("%-5d | ", pages[i]);

    if (!isPresent(frames, numFrames, pages[i])) {
      if (filled < numFrames)
        frames[filled++] = pages[i];
      else {
        int victim = findOptimalVictim(frames, numFrames, pages, n, i);
        frames[victim] = pages[i];
      }
      misses++;

      for (int j = 0; j < numFrames; j++)
        (frames[j] == -1) ? printf("- ") : printf("%d ", frames[j]);
      printf(" *MISS*");
    } else {
      for (int j = 0; j < numFrames; j++)
        (frames[j] == -1) ? printf("- ") : printf("%d ", frames[j]);
      printf(" *HIT*");
    }
    printf("\n");
  }
  printSummary("Optimal", n, misses);
}

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int pages[MAX_PAGES], n, numFrames;

  printf("Enter number of pages: ");
  scanf("%d", &n);

  printf("Enter the reference string: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &pages[i]);

  printf("Enter number of frames: ");
  scanf("%d", &numFrames);

  fifo(pages, n, numFrames);
  lru(pages, n, numFrames);
  optimal(pages, n, numFrames);

  return 0;
}
