#include "scheduling.h"
#include <climits>

void priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0, completed = 0;
    vector<int> rem(n);
    // Initialize remaining time for each process.
    for (int i = 0; i < n; i++) {
        rem[i] = processes[i].burstTime;
    }
    while (completed != n) {
        int idx = -1;
        int highestPriority = INT_MAX; // Lower number = higher priority.
        // Select process based on priority and arrival time.
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && rem[i] > 0) {
                if (processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == highestPriority) {
                    if (processes[i].arrivalTime < processes[idx].arrivalTime)
                        idx = i;
                }
            }
        }
        if (idx == -1) {
            currentTime++; // Idle CPU
            continue;
        }
        // Execute for one time unit.
        rem[idx]--;
        currentTime++;
        if (rem[idx] == 0) {
            completed++;
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
        }
    }
}
