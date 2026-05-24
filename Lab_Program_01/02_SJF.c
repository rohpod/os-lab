//  SJF — Shortest Job First (Non-Preemptive)

#include <stdio.h>

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n], done[n];

  for (int i = 0; i < n; i++) {
    pid[i] = i + 1;
    printf("Enter AT and BT for P%d: ", i + 1);
    scanf("%d %d", &at[i], &bt[i]);
    done[i] = 0;
  }

  // --- Simulate SJF ---
  int time = 0, completed = 0;
  while (completed < n) {

    // Find arrived, not-done process with minimum BT
    int idx = -1;
    for (int i = 0; i < n; i++) {
      if (!done[i] && at[i] <= time) {
        if (idx == -1 || bt[i] < bt[idx])
          idx = i;
      }
    }

    if (idx == -1) {
      time++;
      continue;
    } // CPU idle, advance time

    rt[idx] = time - at[idx]; // RT = start time - AT
    time += bt[idx];          // process runs to completion
    ct[idx] = time;
    tat[idx] = ct[idx] - at[idx]; // TAT = CT - AT
    wt[idx] = tat[idx] - bt[idx]; // WT  = TAT - BT
    done[idx] = 1;
    completed++;
  }

  // --- Sort by PID before printing ---
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (pid[j] > pid[j + 1]) {
        int tmp;
        tmp = pid[j];
        pid[j] = pid[j + 1];
        pid[j + 1] = tmp;
        tmp = at[j];
        at[j] = at[j + 1];
        at[j + 1] = tmp;
        tmp = bt[j];
        bt[j] = bt[j + 1];
        bt[j + 1] = tmp;
        tmp = ct[j];
        ct[j] = ct[j + 1];
        ct[j + 1] = tmp;
        tmp = tat[j];
        tat[j] = tat[j + 1];
        tat[j + 1] = tmp;
        tmp = wt[j];
        wt[j] = wt[j + 1];
        wt[j + 1] = tmp;
        tmp = rt[j];
        rt[j] = rt[j + 1];
        rt[j + 1] = tmp;
      }

  // --- Print Table ---
  printf("\n%-6s %-6s %-6s %-6s %-6s %-6s %-6s\n", "PID", "AT", "BT", "CT",
         "TAT", "WT", "RT");
  printf("------------------------------------------------\n");

  float sumTAT = 0, sumWT = 0, sumRT = 0;
  for (int i = 0; i < n; i++) {
    sumTAT += tat[i];
    sumWT += wt[i];
    sumRT += rt[i];
    printf("P%-5d %-6d %-6d %-6d %-6d %-6d %-6d\n", pid[i], at[i], bt[i], ct[i],
           tat[i], wt[i], rt[i]);
  }

  printf("------------------------------------------------\n");
  printf("Avg TAT: %.2f  |  Avg WT: %.2f  |  Avg RT: %.2f\n", sumTAT / n,
         sumWT / n, sumRT / n);

  return 0;
}
