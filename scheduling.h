#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <vector>
using namespace std;

struct Process {
    int pid;             // Process ID
    int arrivalTime;     // Arrival time of the process
    int burstTime;       // CPU Burst time (original value)
    int remainingTime;   // Remaining time (for preemptive algorithms)
    int priority;        // Priority (lower value = higher priority)
    int completionTime;  // Completion time of the process
    int turnaroundTime;  // Turnaround time = Completion Time - Arrival Time
    int waitingTime;     // Waiting time = Turnaround Time - Burst Time
    bool completed;      // For marking completion in non-preemptive algorithms
};

// Function prototypes for scheduling algorithms
void fcfs(vector<Process>& processes);
void sjf(vector<Process>& processes);
void srtf(vector<Process>& processes);
void priorityScheduling(vector<Process>& processes);
void roundRobin(vector<Process>& processes, int timeQuantum);

double calculateAverageTurnaround(const vector<Process>& processes);
double calculateAverageWaiting(const vector<Process>& processes);

#endif // SCHEDULING_H
