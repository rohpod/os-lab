#include <stdio.h>

int main() {
  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, completed = 0, curr_time = 0, pid[10], at[10], bt[10], remt[10],
         ct[10], tat[10], wt[10], st[10], rt[10], i, j, tq, q[10], f = 0,
         r = -1, inq[10] = {0};
  double tat_sum = 0, wt_sum = 0;

  printf("Enter no. of processes: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    pid[i] = i + 1;

    printf("Enter arrival time for process[%d]: ", i + 1);
    scanf("%d", &at[i]);

    printf("Enter burst time for process[%d]: ", i + 1);
    scanf("%d", &bt[i]);
    remt[i] = bt[i]; // initialising remaining time
  }

  printf("Enter time quantum: ");
  scanf("%d", &tq);

  // running a while loop for each time interval
  // until all the processes have completed
  while (completed != n) {

    // add processes that have arrived to queue
    for (i = 0; i < n; i++) {
      if (at[i] <= curr_time && remt[i] > 0 && !inq[i]) {
        r = (r + 1) % 10;
        q[r] = i;
        inq[i] = 1;
      }
    }

    // CPU idle time
    if (f > r) {
      curr_time++;
      continue;
    }

    // dequeue
    i = q[f];
    f = (f + 1) % 10;
    inq[i] = 0;

    // if the process is in the CPU for the first time
    if (remt[i] == bt[i])
      st[i] = curr_time;

    // decrement the remaining time of the process
    if (remt[i] < tq) {
      curr_time += remt[i];
      remt[i] = 0;
    } else {
      curr_time += tq;
      remt[i] -= tq;
    }

    // add newly arrived processes during execution
    for (j = 0; j < n; j++) {
      if (at[j] <= curr_time && remt[j] > 0 && !inq[j] && j != i) {
        r = (r + 1) % 10;
        q[r] = j;
        inq[j] = 1;
      }
    }

    // if the process has completed
    if (remt[i] == 0) {
      // CT
      ct[i] = curr_time;

      // TAT
      tat[i] = ct[i] - at[i];
      tat_sum += tat[i];

      // WT
      wt[i] = tat[i] - bt[i];
      wt_sum += wt[i];

      // RT
      rt[i] = st[i] - at[i];

      // increment the completed processes count
      completed++;
    } else {
      r = (r + 1) % 10;
      q[r] = i;
      inq[i] = 1;
    }
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
