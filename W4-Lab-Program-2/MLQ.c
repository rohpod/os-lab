#include <stdio.h>

int main() {
  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, curr_time = 0, i, j;
  int ns = 0, nu = 0;
  int type[10], tq;

  int completedSys = 0, completedUsr = 0;

  int q[10], f = 0, r = -1;
  int inq[10] = {0}, remt[10];

  int sysPID[10], sysAT[10], sysBT[10], sysCT[10], sysTAT[10], sysWT[10];
  int usrPID[10], usrAT[10], usrBT[10], usrCT[10], usrTAT[10], usrWT[10];

  double tat_sum = 0, wt_sum = 0;

  printf("Enter no. of processes: ");
  scanf("%d", &n);

  // input
  for (i = 0; i < n; i++) {

    printf("Enter type for process[%d] (0=system, 1=user): ", i + 1);
    scanf("%d", &type[i]);

    printf("Enter AT and BT for process[%d]: ", i + 1);

    if (type[i] == 0) {
      scanf("%d %d", &sysAT[ns], &sysBT[ns]);
      sysPID[ns] = i + 1;
      remt[ns] = sysBT[ns];
      ns++;
    } else {
      scanf("%d %d", &usrAT[nu], &usrBT[nu]);
      usrPID[nu] = i + 1;
      nu++;
    }
  }

  printf("Enter time quantum: ");
  scanf("%d", &tq);

  // run until both queues finished
  while (completedSys < ns || completedUsr < nu) {

    // add system processes to RR queue
    for (i = 0; i < ns; i++) {
      if (sysAT[i] <= curr_time && remt[i] > 0 && !inq[i]) {
        r = (r + 1) % 10;
        q[r] = i;
        inq[i] = 1;
      }
    }

    // ---------- check if system queue empty ----------
    if (f == (r + 1) % 10) {

      int ranUser = 0;

      // run user FCFS if ready
      for (i = 0; i < nu; i++) {

        if (usrBT[i] > 0 && usrAT[i] <= curr_time) {

          curr_time += usrBT[i];

          usrCT[i] = curr_time;

          usrTAT[i] = usrCT[i] - usrAT[i];
          usrWT[i] = usrTAT[i] - usrBT[i];

          tat_sum += usrTAT[i];
          wt_sum += usrWT[i];

          usrBT[i] = 0;
          completedUsr++;

          ranUser = 1;
          break;
        }
      }

      if (!ranUser)
        curr_time++;

      continue;
    }

    // ---------- run system RR ----------
    i = q[f];
    f = (f + 1) % 10;
    inq[i] = 0;

    if (f == (r + 1) % 10) {
      f = 0;
      r = -1;
    }

    if (remt[i] < tq) {
      curr_time += remt[i];
      remt[i] = 0;
    } else {
      curr_time += tq;
      remt[i] -= tq;
    }

    // add new arrivals
    for (j = 0; j < ns; j++) {
      if (sysAT[j] <= curr_time && remt[j] > 0 && !inq[j]) {
        r = (r + 1) % 10;
        q[r] = j;
        inq[j] = 1;
      }
    }

    // finished
    if (remt[i] == 0) {

      sysCT[i] = curr_time;

      sysTAT[i] = sysCT[i] - sysAT[i];
      sysWT[i] = sysTAT[i] - sysBT[i];

      tat_sum += sysTAT[i];
      wt_sum += sysWT[i];

      completedSys++;

    } else {

      r = (r + 1) % 10;
      q[r] = i;
      inq[i] = 1;
    }
  }

  // print
  printf("\nPID\tAT\tBT\tType\tCT\tTAT\tWT\n\n");

  for (j = 1; j <= n; j++) {

    for (i = 0; i < ns; i++) {
      if (sysPID[i] == j) {
        printf("P%d\t%d\t%d\tSystem\t%d\t%d\t%d\n", sysPID[i], sysAT[i],
               sysBT[i], sysCT[i], sysTAT[i], sysWT[i]);
      }
    }

    for (i = 0; i < nu; i++) {
      if (usrPID[i] == j) {
        printf("P%d\t%d\t%d\tUser\t%d\t%d\t%d\n", usrPID[i], usrAT[i], usrBT[i],
               usrCT[i], usrTAT[i], usrWT[i]);
      }
    }
  }

  printf("\nAverage TAT: %.2f\n", tat_sum / n);
  printf("Average WT: %.2f\n", wt_sum / n);

  return 0;
}
