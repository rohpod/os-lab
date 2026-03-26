// Earliest Deadline First

#include <stdio.h>

struct Task {
  int id;
  int execution;
  int period;
  int deadline; // relative deadline
  int remaining;
  int next_release;
  int abs_deadline; // absolute deadline
};

int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int lcm(int a, int b) { return (a * b) / gcd(a, b); }

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, i, t, hyper = 1;

  printf("Enter number of tasks: ");
  scanf("%d", &n);

  struct Task task[n];

  for (i = 0; i < n; i++) {
    task[i].id = i + 1;

    printf("\nTask %d Execution Time: ", i + 1);
    scanf("%d", &task[i].execution);

    printf("Task %d Period: ", i + 1);
    scanf("%d", &task[i].period);

    printf("Task %d Deadline: ", i + 1);
    scanf("%d", &task[i].deadline);

    task[i].remaining = 0;
    task[i].next_release = 0;
    task[i].abs_deadline = 0;
  }

  // Hyperperiod
  for (i = 0; i < n; i++) {
    hyper = lcm(hyper, task[i].period);
  }

  printf("\nHyperperiod = %d\n", hyper);
  printf("\nTime\tRunning Task\n");

  for (t = 0; t < hyper; t++) {
    // Release tasks
    for (i = 0; i < n; i++) {
      if (t == task[i].next_release) {
        task[i].remaining = task[i].execution;
        task[i].abs_deadline = t + task[i].deadline;
        task[i].next_release += task[i].period;
      }
    }

    int best = -1;

    // Choose earliest deadline
    for (i = 0; i < n; i++) {
      if (task[i].remaining > 0) {
        if (best == -1 || task[i].abs_deadline < task[best].abs_deadline) {
          best = i;
        }
      }
    }

    if (best != -1) {
      printf("%d\tT%d\n", t, task[best].id);
      task[best].remaining--;
    } else {
      printf("%d\tIdle\n", t);
    }
  }

  return 0;
}
