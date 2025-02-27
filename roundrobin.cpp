#include "scheduling.h"
#include <queue>
#include <algorithm>

void roundRobin(vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    int currentTime = 0;
    queue<int> q;
    vector<bool> visited(n, false);
    
    // Find the first process to arrive and start from its arrival time.
    int firstIndex = 0;
    int minArrival = processes[0].arrivalTime;
    for (int i = 1; i < n; i++) {
        if (processes[i].arrivalTime < minArrival) {
            minArrival = processes[i].arrivalTime;
            firstIndex = i;
        }
    }
    currentTime = processes[firstIndex].arrivalTime;
    q.push(firstIndex);
    visited[firstIndex] = true;
    
    vector<int> rem(n);
    // Initialize remaining time.
    for (int i = 0; i < n; i++) {
        rem[i] = processes[i].burstTime;
    }
    
    while (!q.empty()) {
        int idx = q.front();
        q.pop();
        visited[idx] = false;
        
        // Process execution for a time slice.
        if (rem[idx] > timeQuantum) {
            rem[idx] -= timeQuantum;
            currentTime += timeQuantum;
        } else {
            currentTime += rem[idx];
            rem[idx] = 0;
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
        }
        
        // Enqueue any processes that have arrived by the current time.
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && rem[i] > 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
        
        // If current process is not finished, add it back to the queue.
        if (rem[idx] > 0) {
            q.push(idx);
            visited[idx] = true;
        }
        
        // If the queue is empty but there are processes yet to arrive, move time forward.
        if (q.empty()) {
            for (int i = 0; i < n; i++) {
                if (rem[i] > 0) {
                    q.push(i);
                    visited[i] = true;
                    currentTime = max(currentTime, processes[i].arrivalTime);
                    break;
                }
            }
        }
    }
}
