#include "scheduling.h"
#include <climits>

void sjf(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0, completed = 0;
    // Reset the completed flag for each process.
    for(auto &p : processes)
        p.completed = false;
    
    while (completed != n) {
        int idx = -1;
        int minBurst = INT_MAX;
        // Select process with smallest burst time among processes that have arrived.
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    idx = i;
                }
                // Tie-breaker: choose the process with earlier arrival time.
                else if (processes[i].burstTime == minBurst) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime)
                        idx = i;
                }
            }
        }
        if (idx == -1) {
            // No process is available; increment time.
            currentTime++;
        } else {
            currentTime += processes[idx].burstTime;
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            processes[idx].completed = true;
            completed++;
        }
    }
}
