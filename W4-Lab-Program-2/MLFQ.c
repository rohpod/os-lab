#include <stdio.h>

int main() {
  printf("Name: ROHAN PODDAR\nUSN:1WA24CS238\n\n");

  int n, curr_time = 0, i, j, ns = 0, nu = 0, type[10];
  int sysPID[10], sysAT[10], sysBT[10], sysCT[10], sysTAT[10], sysWT[10];
  int usrPID[10], usrAT[10], usrBT[10], usrCT[10], usrTAT[10], usrWT[10];
  double tat_sum = 0, wt_sum = 0;

  printf("Enter no. of processes: ");
  scanf("%d", &n);

  // input
  for (i = 0; i < n; i++) {

    // process type
    printf("Enter type for process[%d] (0=system, 1=user): ", i + 1);
    scanf("%d", &type[i]);

    // at and bt of the process
    printf("Enter AT and BT for process[%d]: ", i + 1);

    // storing the info in relevant type
    if (type[i] == 0) {
      scanf("%d %d", &sysAT[ns], &sysBT[ns]);
      sysPID[ns] = i + 1;
      ns++;
    } else {
      scanf("%d %d", &usrAT[nu], &usrBT[nu]);
      usrPID[nu] = i + 1;
      nu++;
    }
  }

  // system queue (FCFS)
  for (i = 0; i < ns; i++) {

    if (curr_time < sysAT[i])
      curr_time = sysAT[i];

    curr_time += sysBT[i];

    // CT
    sysCT[i] = curr_time;

    // TAT
    sysTAT[i] = sysCT[i] - sysAT[i];
    tat_sum += sysTAT[i];

    // WT
    sysWT[i] = sysTAT[i] - sysBT[i];
    wt_sum += sysWT[i];
  }

  // user queue (FCFS)
  for (i = 0; i < nu; i++) {

    if (curr_time < usrAT[i])
      curr_time = usrAT[i];

    curr_time += usrBT[i];

    // CT
    usrCT[i] = curr_time;

    // TAT
    usrTAT[i] = usrCT[i] - usrAT[i];
    tat_sum += usrTAT[i];

    // WT
    usrWT[i] = usrTAT[i] - usrBT[i];
    wt_sum += usrWT[i];
  }

  // header row
  printf("\nPID\tAT\tBT\tType\tCT\tTAT\tWT\n\n");

  for (j = 1; j <= n; j++) {

    // search system queue
    for (i = 0; i < ns; i++) {
      if (sysPID[i] == j) {
        printf("P%d\t%d\t%d\tSystem\t%d\t%d\t%d\n", sysPID[i], sysAT[i],
               sysBT[i], sysCT[i], sysTAT[i], sysWT[i]);
      }
    }

    // search user queue
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
