#include "scheduling.h"

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
