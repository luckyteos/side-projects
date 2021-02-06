#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int roundRobinScheduler(void);
int SJFNonPreemptScheduler(void);
int FCFSScheduler(void);

int main(void) {
  SJFNonPreemptScheduler();
}

int roundRobinScheduler(void){
  int numProc, tsSize, currentCpuTime = 0, remainTime = 0;
  double compSum = 0, waitSum = 0;
  bool schComplete = false;

  printf("Enter the number of processes in the system\n");
  scanf("%d", &numProc);

  int cpuBurst[numProc], completionTime[numProc], remainBurst[numProc];

  for (int i = 0; i < numProc; i++){
      printf("Enter the burst times for process %d\n", i+1);
      scanf("%d", &cpuBurst[i]);
      remainBurst[i] = cpuBurst[i];
  }

  printf("Enter the length of the time slice\n");
  scanf("%d", &tsSize);

//Algorithm
//First Process in cpuBurst queue executes

//Check if its burst time is more than time slice
//If more execute during the whole time slice
//Put remaining burst time back in array

//Else execute only the required burst time

// Add time slice to CPU Time

//If burst time equals 0, store currentCpuTime as completionTime of process

//Go to next process
//repeat

//If completionTime of process(i) + 1 is not set (0), then continue loop
while (!schComplete) {
  //Resetting remainTime for a new cycle through of the processes
  remainTime = 0;
  for (int i = 0; i < sizeof(remainBurst)/sizeof(remainBurst[0]); i++){
      if (remainBurst[i] > tsSize){
          remainBurst[i] -= tsSize;
          currentCpuTime += tsSize;
          // Important for burst time to be more than zero if not completion time will be inaccurate
      } else if (remainBurst[i] > 0 && remainBurst[i] <= tsSize) {
          currentCpuTime += remainBurst[i];
          remainBurst[i] -= remainBurst[i];
          completionTime[i] = currentCpuTime;
      }
      remainTime += remainBurst[i];
      printf("Remaining time is %d\n", remainTime);
  }
  // This check is important. If remainTime is zero it means all processes have completed execution
  if (remainTime == 0){
      schComplete = true;
  }
}

//Calculate sum of completion and wait times
for (int i = 0; i < sizeof(completionTime)/sizeof(completionTime[0]); i++) {
    int taTime = completionTime[i] - 0;
    int waitTime = completionTime[i] - cpuBurst[i];
    printf("Turnaround time for process %d is %d\n", i+1, taTime);
    printf("Waiting time for process %d is %d\n", i+1, waitTime);
    compSum += taTime;
    waitSum += waitTime;
}

printf("Average turnaround time is %.2f\n", compSum/numProc);
printf("Average waiting time is %.2f\n", waitSum/numProc);

return 0;
}

int SJFNonPreemptScheduler(void){
  int numProc;
  double burstSum, waitSum;

  printf("Enter the number of processes in the system\n");
  scanf("%d", &numProc);

  int burstTimes[numProc], procOrder[numProc];
  double burstSums[numProc], waitSums[numProc];

  for (int i = 0; i < numProc; i++){
      printf("Enter the burst times for process %d\n", i+1);
      scanf("%d", &burstTimes[i]);
      procOrder[i] = i+1;
  }

  for (int i = 0; i < sizeof(burstTimes)/sizeof(burstTimes[0]); i++){
      for (int z = i + 1; z < sizeof(burstTimes)/sizeof(burstTimes[0]); z++){
          if (burstTimes[i] > burstTimes[z]){
              //Switch the process order of the processes
              int tempOrder = procOrder[i];
              procOrder[i] = procOrder[z];
              procOrder[z] = tempOrder;

              //Sort the burst times by order
              int tempTime = burstTimes[i];
              burstTimes[i] = burstTimes[z];
              burstTimes[z] = tempTime;
          } 
      }

      burstSum += burstTimes[i];
      waitSum += burstSum - burstTimes[i];
      //These arrays are just to arrange the output in ascending order of process number
      burstSums[procOrder[i]-1] = burstSum;
      waitSums[procOrder[i]-1] = burstSum - burstTimes[i];
      printf("Process %d executes\n", procOrder[i]);
      //printf("Process %d has burst time %d\n", procOrder[i], burstTimes[i]);
      //printf("Process %d has turnaround time %.2f\n", procOrder[i], burstSum);
      //printf("Process %d has waiting time %.2f\n", procOrder[i], burstSum - burstTimes[i]);
  }

  //Print output in ascending order of process number
  for (int j = 0; j < sizeof(burstSums)/sizeof(burstSums[0]); j++){
      printf("Process %d has turnaround time %.2f, waiting time %.2f\n", j+1, burstSums[j], waitSums[j]);
  }
  
  printf("Average turnaround time is %.2f\n", burstSum/numProc);
  printf("Average waiting time is %.2f\n", waitSum/numProc);


  return 0;
}

int FCFSScheduler(void){
  int numProc, prevRandNum = 0;
  double burstSum, waitSum;
  //Intialize seed for rand
  srand(time(0));

  printf("Enter the number of processes in the system\n");
  scanf("%d", &numProc);

  int cpuBurst[numProc];

  for (int i = 0; i < numProc; i++){
      printf("Enter the burst times for process %d\n", i+1);
      scanf("%d", &cpuBurst[i]);
  }

  for (int x = 0; x < sizeof(cpuBurst)/sizeof(cpuBurst[0]); x++){
      burstSum += cpuBurst[x];
      waitSum += burstSum - cpuBurst[x];

      printf("Process %d has burst time %d\n", x+1, cpuBurst[x]);
      printf("Process %d has turnaround time %d\n", x+1, cpuBurst[x]);
      printf("Process %d has waiting time %.2f\n", x+1, burstSum - cpuBurst[x]);
  }

  printf("Average turnaround time is %.2f\n", burstSum/numProc);
  printf("Average waiting time is %.2f\n", waitSum/numProc);

  return 0;
}