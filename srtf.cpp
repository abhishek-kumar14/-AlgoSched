#include "scheduling.h"
#include <climits>

void srtf(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0, completed = 0;
    vector<int> rem(n);
    // Initialize remaining time for each process.
    for (int i = 0; i < n; i++) {
        rem[i] = processes[i].burstTime;
    }
    while (completed != n) {
        int idx = -1;
        int minRemaining = INT_MAX;
        // Find process with smallest remaining time among arrived processes.
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && rem[i] > 0 && rem[i] < minRemaining) {
                minRemaining = rem[i];
                idx = i;
            }
        }
        if (idx == -1) {
            currentTime++; // CPU idle
            continue;
        }
        // Execute the selected process for one time unit.
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
