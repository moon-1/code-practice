practice_code (operation system)

This is round robin and FCFS algorithm program

Input format :
myscheduler (process information text file) (algorithm option 1: FCFS, 0: RR) (if RR, you can input time quantum)

Input example :

FCFS>
myscheduler input10.txt 0 

RR>
myscheduler input10.txt 1 4

program will be show you average CPU burst time, average waiting time, average turn around time, average response time, and total number of context switching performed time.

and, input text file format have to be like this.
(pid, arrival time, CPU burst time) 
  1    0    1
  2    2    7
  3    3    6
  4    5    5
  5    6    2
  6   10    4
  7   12    3
  8   13    9
  9   17   10
 10   18    8