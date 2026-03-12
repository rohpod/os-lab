#include <stdio.h>

int main() {
  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, curr_time = 0, pid[10], at[10], bt[10], ct[10], tat[10], wt[10],
         st[10], rt[10], i, j, temp, completed = 0, done[10] = {0};
  double tat_sum = 0, wt_sum = 0;

  printf("Enter no. of processes: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    pid[i] = i + 1;

    printf("Enter arrival time for process[%d]: ", i + 1);
    scanf("%d", &at[i]);

    printf("Enter burst time for process[%d]: ", i + 1);
    scanf("%d", &bt[i]);
  }

  // sorting the processes by AT
  for (i = 0; i < n; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (at[j] > at[j + 1]) {
        // swapping PID, AT, and BT
        temp = pid[j];
        pid[j] = pid[j + 1];
        pid[j + 1] = temp;
        temp = at[j];
        at[j] = at[j + 1];
        at[j + 1] = temp;
        temp = bt[j];
        bt[j] = bt[j + 1];
        bt[j + 1] = temp;
      }
    }
  }

  while (completed != n) {
    int min = 99999999, // to set the lowest remaining time
        s = -1;         // index of the process with the shortest remaining time

    for (i = 0; i < n; i++) {
      // 1. AT is now or before current time
      // 2. check if the process is not completed
      // 3. least burst time
      if (at[i] <= curr_time && !done[i] && bt[i] < min) {
        min = bt[i];
        s = i;
      }
    }

    // CPU idle time
    if (s == -1) {
      curr_time++;
      continue;
    }

    // set the start time
    st[s] = curr_time;

    curr_time += bt[s];

    // CT
    ct[s] = curr_time;

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
    done[s] = 1;
  }

  // header row
  printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n\n");

  // sorted by PID
  for (j = 1; j < n + 1; j++) {
    for (i = 0; i < n; i++) {
      if (pid[i] == j)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i],
               tat[i], wt[i], rt[i]);
    }
  }

  printf("\nAverage TAT: %.2f\n", (tat_sum / n));
  printf("Average WT: %.2f\n", (wt_sum / n));

  return 0;
}
