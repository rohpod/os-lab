// File Organization Techniques: Hierarchical

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20
#define MAX_CHILDREN 10

// Each node is a file OR a directory
typedef struct Node {
  char name[NAME_LEN];
  int isDir; // 1 = directory, 0 = file
  struct Node *children[MAX_CHILDREN];
  int childCount;
} Node;

Node *createNode(char *name, int isDir) {
  Node *n = (Node *)malloc(sizeof(Node));
  strcpy(n->name, name);
  n->isDir = isDir;
  n->childCount = 0;
  return n;
}

// Find a direct child of 'parent' by name
Node *findChild(Node *parent, char *name) {
  for (int i = 0; i < parent->childCount; i++)
    if (strcmp(parent->children[i]->name, name) == 0)
      return parent->children[i];
  return NULL;
}

// Insert a file or subdirectory under a given parent directory name
void insert(Node *root, char *parentName, char *childName, int isDir) {
  // BFS to find the parent directory
  Node *queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;
  while (front < rear) {
    Node *curr = queue[front++];
    if (strcmp(curr->name, parentName) == 0 && curr->isDir) {
      if (findChild(curr, childName)) {
        printf("'%s' already exists in '%s'.\n", childName, parentName);
        return;
      }
      curr->children[curr->childCount++] = createNode(childName, isDir);
      printf("%s '%s' created under '%s'.\n", isDir ? "Directory" : "File",
             childName, parentName);
      return;
    }
    for (int i = 0; i < curr->childCount; i++)
      if (curr->children[i]->isDir)
        queue[rear++] = curr->children[i];
  }
  printf("Parent directory '%s' not found.\n", parentName);
}

// Recursive display with indentation
void display(Node *node, int level) {
  for (int i = 0; i < level; i++)
    printf("  ");
  printf("%s %s\n", node->isDir ? "[DIR]" : "[FILE]", node->name);
  for (int i = 0; i < node->childCount; i++)
    display(node->children[i], level + 1);
}

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  Node *root = createNode("root", 1); // root is always a directory
  int choice;
  char parent[NAME_LEN], child[NAME_LEN];
  do {
    printf("\n1.Add Directory  2.Add File  3.Display  0.Exit\nChoice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("Parent directory: ");
      scanf("%s", parent);
      printf("New directory name: ");
      scanf("%s", child);
      insert(root, parent, child, 1);
      break;
    case 2:
      printf("Parent directory: ");
      scanf("%s", parent);
      printf("File name: ");
      scanf("%s", child);
      insert(root, parent, child, 0);
      break;
    case 3:
      printf("\n--- Hierarchical Directory ---\n");
      display(root, 0);
      break;
    }
  } while (choice != 0);
  return 0;
}
