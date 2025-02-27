#include <iostream>
#include <vector>
#include "scheduling.h"

using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    
    // Collect process details.
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].pid = i;
        processes[i].remainingTime = processes[i].burstTime; // initialize remainingTime
    }
    
    int timeQuantum;
    cout << "Enter time quantum for Round Robin: ";
    cin >> timeQuantum;
    
    // Make copies for each scheduling algorithm.
    vector<Process> fcfsProcesses = processes;
    vector<Process> sjfProcesses = processes;
    vector<Process> srtfProcesses = processes;
    vector<Process> priorityProcesses = processes;
    vector<Process> rrProcesses = processes;
    
    // Run FCFS Scheduling.
    fcfs(fcfsProcesses);
    cout << "\nFCFS Scheduling Results:\n";
    cout << "Average Turnaround Time: " << calculateAverageTurnaround(fcfsProcesses) << "\n";
    cout << "Average Waiting Time: " << calculateAverageWaiting(fcfsProcesses) << "\n";
    
    // Run SJF Scheduling.
    sjf(sjfProcesses);
    cout << "\nSJF (Non-Preemptive) Scheduling Results:\n";
    cout << "Average Turnaround Time: " << calculateAverageTurnaround(sjfProcesses) << "\n";
    cout << "Average Waiting Time: " << calculateAverageWaiting(sjfProcesses) << "\n";
    
    // Run SRTF Scheduling.
    srtf(srtfProcesses);
    cout << "\nSRTF (Preemptive) Scheduling Results:\n";
    cout << "Average Turnaround Time: " << calculateAverageTurnaround(srtfProcesses) << "\n";
    cout << "Average Waiting Time: " << calculateAverageWaiting(srtfProcesses) << "\n";
    
    // Run Priority Scheduling.
    priorityScheduling(priorityProcesses);
    cout << "\nPriority (Preemptive) Scheduling Results:\n";
    cout << "Average Turnaround Time: " << calculateAverageTurnaround(priorityProcesses) << "\n";
    cout << "Average Waiting Time: " << calculateAverageWaiting(priorityProcesses) << "\n";
    
    // Run Round Robin Scheduling.
    roundRobin(rrProcesses, timeQuantum);
    cout << "\nRound Robin Scheduling Results:\n";
    cout << "Average Turnaround Time: " << calculateAverageTurnaround(rrProcesses) << "\n";
    cout << "Average Waiting Time: " << calculateAverageWaiting(rrProcesses) << "\n";
    
    return 0;
}
