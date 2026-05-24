//  Round Robin — Preemptive

#include <stdio.h>

int main() {

  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, tq;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  int pid[n], at[n], bt[n], rem[n], ct[n], tat[n], wt[n], rt[n], started[n],
      inQueue[n];

  for (int i = 0; i < n; i++) {
    pid[i] = i + 1;
    printf("Enter AT and BT for P%d: ", i + 1);
    scanf("%d %d", &at[i], &bt[i]);
    started[i] = 0;
    inQueue[i] = 0;
  }

  printf("Enter Time Quantum: ");
  scanf("%d", &tq);

  // --- Sort by Arrival Time ---
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

  // Initialize rem after sort
  for (int i = 0; i < n; i++)
    rem[i] = bt[i];

  // --- Queue Setup ---
  int queue[1000], front = 0, rear = 0;

  int time = 0, completed = 0;

  // Start time at first arrival, seed queue with all processes arriving then
  time = at[0];
  for (int i = 0; i < n; i++)
    if (at[i] <= time) {
      queue[rear++] = i;
      inQueue[i] = 1;
    }

  // --- Simulate Round Robin ---
  while (completed < n) {

    if (front == rear) { // queue empty, CPU idle
      time++;
      for (int i = 0; i < n; i++) // check for new arrivals
        if (!inQueue[i] && rem[i] > 0 && at[i] <= time) {
          queue[rear++] = i;
          inQueue[i] = 1;
        }
      continue;
    }

    int idx = queue[front++]; // dequeue next process

    // Capture RT on first execution
    if (!started[idx]) {
      rt[idx] = time - at[idx]; // RT = first start - AT
      started[idx] = 1;
    }

    int exec = (rem[idx] < tq) ? rem[idx] : tq; // run for min(rem, tq)
    rem[idx] -= exec;
    time += exec;

    // Add newly arrived processes after this quantum
    for (int i = 0; i < n; i++)
      if (!inQueue[i] && rem[i] > 0 && at[i] <= time) {
        queue[rear++] = i;
        inQueue[i] = 1;
      }

    if (rem[idx] == 0) { // process finished
      ct[idx] = time;
      tat[idx] = ct[idx] - at[idx]; // TAT = CT - AT
      wt[idx] = tat[idx] - bt[idx]; // WT  = TAT - BT
      completed++;
    } else {
      queue[rear++] = idx; // re-add to back of queue
    }
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
