#include <stdio.h>

int main() {
  int n, curr_time = 0, pid[10], at[10], bt[10], ct[10], tat[10], wt[10],
         st[10], rt[10], i, j, temp;
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

  // CT
  for (i = 0; i < n; i++) {
    // CPU idle time
    if (curr_time < at[i]) {
      curr_time = at[i];
    }

    // calculating start time for RT
    st[i] = curr_time;

    curr_time += bt[i];
    ct[i] = curr_time;
  }

  // TAT
  for (i = 0; i < n; i++) {
    tat[i] = ct[i] - at[i];
    tat_sum += tat[i];
  }

  // WT
  for (i = 0; i < n; i++) {
    wt[i] = tat[i] - bt[i];
    wt_sum += wt[i];
  }

  // RT
  for (i = 0; i < n; i++) {
    rt[i] = st[i] - at[i];
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

  // sorted by AT
  // for (i = 0; i < n; i++)
  //   printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i],
  //   tat[i], wt[i], rt[i]);

  printf("\nAverage TAT: %.2f\n", (tat_sum / n));
  printf("Average WT: %.2f\n", (wt_sum / n));

  return 0;
}
