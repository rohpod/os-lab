#include <stdio.h>

int main() {
  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, curr_time = 0, pid[10], at[10], bt[10], remt[10], p[10], ct[10],
         tat[10], wt[10], st[10], rt[10], i, j, completed = 0, choice;
  double tat_sum = 0, wt_sum = 0;

  printf("Enter no. of processes: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    pid[i] = i + 1;

    printf("Enter arrival time for process[%d]: ", i + 1);
    scanf("%d", &at[i]);

    printf("Enter burst time for process[%d]: ", i + 1);
    scanf("%d", &bt[i]);
    remt[i] = bt[i];

    printf("Enter priority for process[%d]: ", i + 1);
    scanf("%d", &p[i]);
  }

  printf("\nType:\n");
  printf("1. Lower the number higher the priority\n");
  printf("2. Higher the number higher the priority\n");
  printf("Choice: ");
  scanf("%d", &choice);

  while (completed != n) {

    int min = 99999999,  // to set with the lowest priority
        max = -99999999, // to set with the highest priority
        s = -1; // index of the process with the lowest/highest priority

    for (i = 0; i < n; i++) {
      // 1. AT is now or before current time
      // 2. priority is lesser than min
      // 3. there is some time remaining
      if (choice == 1) {
        if (at[i] <= curr_time && p[i] < min && remt[i] > 0) {
          min = p[i];
          s = i;
        }
      }
      if (choice == 2) {
        if (at[i] <= curr_time && p[i] > max && remt[i] > 0) {
          max = p[i];
          s = i;
        }
      }
    }

    // CPU idle time
    if (s == -1) {
      curr_time++;
      continue;
    }

    // if the process is in the CPU for the first time
    if (remt[s] == bt[s])
      st[s] = curr_time;

    // decrement the remaining time of the process
    remt[s]--;

    // if the process has completed
    if (remt[s] == 0) {
      // CT
      ct[s] = curr_time + 1;

      // TAT
      tat[s] = ct[s] - at[s];
      tat_sum += tat[s];

      // WT
      wt[s] = tat[s] - bt[s];
      wt_sum += wt[s];

      // RT
      rt[s] = st[s] - at[s];

      // increment the completed processes count
      completed++;
    }
    curr_time++;
  }

  // header row
  printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n\n");

  // sorted by PID
  for (j = 1; j < n + 1; j++) {
    for (i = 0; i < n; i++) {
      if (pid[i] == j)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], p[i],
               ct[i], tat[i], wt[i], rt[i]);
    }
  }

  printf("\nAverage TAT: %.2f\n", (tat_sum / n));
  printf("Average WT: %.2f\n", (wt_sum / n));

  return 0;
}
