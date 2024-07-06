#include <iostream>
#include <algorithm>
#include <vector>

struct Process {
    int pid;       // Process ID
    int burstTime; // Burst time
    int waitTime;  // Waiting time
    int turnAroundTime; // Turnaround time
};

bool compareBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

void calculateWaitTime(std::vector<Process>& processes) {
    processes[0].waitTime = 0;

    for (size_t i = 1; i < processes.size(); ++i) {
        processes[i].waitTime = processes[i - 1].waitTime + processes[i - 1].burstTime;
    }
}

void calculateTurnAroundTime(std::vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].turnAroundTime = processes[i].burstTime + processes[i].waitTime;
    }
}

void calculateAverageTimes(std::vector<Process>& processes) {
    int totalWaitTime = 0, totalTurnAroundTime = 0;

    for (const auto& process : processes) {
        totalWaitTime += process.waitTime;
        totalTurnAroundTime += process.turnAroundTime;
    }

    double averageWaitTime = static_cast<double>(totalWaitTime) / processes.size();
    double averageTurnAroundTime = static_cast<double>(totalTurnAroundTime) / processes.size();

    std::cout << "Average waiting time = " << averageWaitTime << "\n";
    std::cout << "Average turnaround time = " << averageTurnAroundTime << "\n";
}

void printProcessDetails(const std::vector<Process>& processes) {
    std::cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        std::cout << process.pid << "\t" << process.burstTime << "\t\t" 
                  << process.waitTime << "\t\t" << process.turnAroundTime << "\n";
    }
}

int main() {
    std::vector<Process> processes = {
        {1, 6, 0, 0}, 
        {2, 8, 0, 0}, 
        {3, 7, 0, 0}, 
        {4, 3, 0, 0}
    };

    std::sort(processes.begin(), processes.end(), compareBurstTime);

    calculateWaitTime(processes);
    calculateTurnAroundTime(processes);
    calculateAverageTimes(processes);
    printProcessDetails(processes);

    return 0;
}
