// File Organization Techniques: Two Level

#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_FILES 10
#define NAME_LEN 20

// User File Directory (UFD)
typedef struct {
  char username[NAME_LEN];
  char files[MAX_FILES][NAME_LEN];
  int fileCount;
} UserDirectory;

// Master File Directory (MFD)
UserDirectory mfd[MAX_USERS];
int userCount = 0;

// Returns index of user, or -1 if not found
int findUser(char *username) {
  for (int i = 0; i < userCount; i++)
    if (strcmp(mfd[i].username, username) == 0)
      return i;
  return -1;
}

void addUser(char *username) {
  if (findUser(username) != -1) {
    printf("User '%s' already exists.\n", username);
    return;
  }
  strcpy(mfd[userCount].username, username);
  mfd[userCount].fileCount = 0;
  userCount++;
  printf("User '%s' added.\n", username);
}

void createFile(char *username, char *filename) {
  int u = findUser(username);
  if (u == -1) {
    printf("User '%s' not found.\n", username);
    return;
  }
  for (int i = 0; i < mfd[u].fileCount; i++) {
    if (strcmp(mfd[u].files[i], filename) == 0) {
      printf("File '%s' already exists for user '%s'.\n", filename, username);
      return;
    }
  }
  strcpy(mfd[u].files[mfd[u].fileCount++], filename);
  printf("File '%s' created for user '%s'.\n", filename, username);
}

void listFiles() {
  printf("\n--- Master File Directory ---\n");
  for (int i = 0; i < userCount; i++) {
    printf("User: %s\n", mfd[i].username);
    if (mfd[i].fileCount == 0) {
      printf("  (no files)\n");
      continue;
    }
    for (int j = 0; j < mfd[i].fileCount; j++)
      printf("  |-- %s\n", mfd[i].files[j]);
  }
}

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int choice;
  char uname[NAME_LEN], fname[NAME_LEN];
  do {
    printf("\n1.Add User  2.Create File  3.List  0.Exit\nChoice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("Username: ");
      scanf("%s", uname);
      addUser(uname);
      break;
    case 2:
      printf("Username: ");
      scanf("%s", uname);
      printf("File name: ");
      scanf("%s", fname);
      createFile(uname, fname);
      break;
    case 3:
      listFiles();
      break;
    }
  } while (choice != 0);
  return 0;
}
