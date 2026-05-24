// File Organization Techniques: Single Level

#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define NAME_LEN 20

// Single directory shared by all users
char directory[MAX_FILES][NAME_LEN];
int fileCount = 0;

void createFile(char *name) {
  for (int i = 0; i < fileCount; i++) {
    if (strcmp(directory[i], name) == 0) {
      printf("Error: File '%s' already exists. (Naming Collision)\n", name);
      return;
    }
  }
  strcpy(directory[fileCount++], name);
  printf("File '%s' created.\n", name);
}

void deleteFile(char *name) {
  for (int i = 0; i < fileCount; i++) {
    if (strcmp(directory[i], name) == 0) {
      for (int j = i; j < fileCount - 1; j++)
        strcpy(directory[j], directory[j + 1]);
      fileCount--;
      printf("File '%s' deleted.\n", name);
      return;
    }
  }
  printf("Error: File '%s' not found.\n", name);
}

void listFiles() {
  printf("\n--- Single-Level Directory ---\n");
  if (fileCount == 0) {
    printf("Directory is empty.\n");
    return;
  }
  for (int i = 0; i < fileCount; i++)
    printf("  [%d] %s\n", i + 1, directory[i]);
}

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int choice;
  char name[NAME_LEN];
  do {
    printf("\n1.Create  2.Delete  3.List  0.Exit\nChoice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("File name: ");
      scanf("%s", name);
      createFile(name);
      break;
    case 2:
      printf("File name: ");
      scanf("%s", name);
      deleteFile(name);
      break;
    case 3:
      listFiles();
      break;
    }
  } while (choice != 0);
  return 0;
}
