#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

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

// FCFS Scheduling (Non-preemptive)
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

// SJF Scheduling (Non-preemptive)
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

// SRTF Scheduling (Preemptive)
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

// Priority Scheduling (Preemptive)
// Lower numeric value indicates higher priority.
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

// Round Robin Scheduling (Preemptive)
void roundRobin(vector<Process>& processes, int timeQuantum) {
    int n = processes.size();
    int currentTime = 0;
    queue<int> q;
    vector<bool> visited(n, false);
    
    // Find the first process to arrive and start from its arrival time.
    int firstIndex = 0;
    int minArrival = INT_MAX;
    for (int i = 0; i < n; i++) {
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
        
        // If queue is empty but some processes have not yet arrived,
        // move the time forward to the next arrival.
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

// Utility functions to compute averages.
double calculateAverageTurnaround(const vector<Process>& processes) {
    double total = 0;
    for(const auto &p : processes)
        total += p.turnaroundTime;
    return total / processes.size();
}

double calculateAverageWaiting(const vector<Process>& processes) {
    double total = 0;
    for(const auto &p : processes)
        total += p.waitingTime;
    return total / processes.size();
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    
    // Collect process details.
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time, burst time, and priority for process " << i+1 << ": ";
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
