//  FCFS — First Come First Serve (Non-Preemptive)

#include <stdio.h>

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n];

  for (int i = 0; i < n; i++) {
    pid[i] = i + 1;
    printf("Enter AT and BT for P%d: ", i + 1);
    scanf("%d %d", &at[i], &bt[i]);
  }

  // --- Sort by Arrival Time (Bubble Sort) ---
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (at[j] > at[j + 1]) {
        int tmp;
        tmp = at[j];
        at[j] = at[j + 1];
        at[j + 1] = tmp;
        tmp = bt[j];
        bt[j] = bt[j + 1];
        bt[j + 1] = tmp;
        tmp = pid[j];
        pid[j] = pid[j + 1];
        pid[j + 1] = tmp;
      }

  // --- Completion Time ---
  // First process: starts at its own AT
  ct[0] = at[0] + bt[0];
  for (int i = 1; i < n; i++) {
    // If CPU is free before next process arrives, it waits
    int start = (ct[i - 1] < at[i]) ? at[i] : ct[i - 1];
    ct[i] = start + bt[i];
  }

  // --- TAT, WT, RT ---
  float sumTAT = 0, sumWT = 0, sumRT = 0;
  for (int i = 0; i < n; i++) {
    tat[i] = ct[i] - at[i]; // TAT = CT - AT
    wt[i] = tat[i] - bt[i]; // WT  = TAT - BT
    rt[i] = wt[i];          // RT  = WT  (FCFS: no preemption)
    sumTAT += tat[i];
    sumWT += wt[i];
    sumRT += rt[i];
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
  for (int i = 0; i < n; i++)
    printf("P%-5d %-6d %-6d %-6d %-6d %-6d %-6d\n", pid[i], at[i], bt[i], ct[i],
           tat[i], wt[i], rt[i]);

  printf("------------------------------------------------\n");
  printf("Avg TAT: %.2f  |  Avg WT: %.2f  |  Avg RT: %.2f\n", sumTAT / n,
         sumWT / n, sumRT / n);

  return 0;
}
