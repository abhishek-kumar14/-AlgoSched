#include "scheduling.h"
#include <algorithm>

void fcfs(vector<Process>& processes) {
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });
    int currentTime = 0;
    for(auto &p : processes) {
        if(currentTime < p.arrivalTime)
            currentTime = p.arrivalTime;  // Idle CPU until process arrives
        currentTime += p.burstTime;
        p.completionTime = currentTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
    }
}
