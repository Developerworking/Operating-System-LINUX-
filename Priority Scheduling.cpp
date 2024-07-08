#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid; // Process ID
    int burstTime; // Burst Time
    int priority; // Priority
    int waitingTime; // Waiting Time
    int turnAroundTime; // Turnaround Time
};

// Function to sort processes based on priority
bool compare(Process a, Process b) {
    return a.priority > b.priority;
}

void findWaitingTime(vector<Process>& processes) {
    processes[0].waitingTime = 0;

    for (size_t i = 1; i < processes.size(); ++i) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void findTurnAroundTime(vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void findAvgTime(vector<Process>& processes) {
    findWaitingTime(processes);
    findTurnAroundTime(processes);

    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    cout << "\nProcesses  " << " Burst time  "
         << " Waiting time  " << " Turn around time\n";

    for (size_t i = 0; i < processes.size(); ++i) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        cout << "   " << processes[i].pid << "\t\t"
             << processes[i].burstTime << "\t    "
             << processes[i].waitingTime << "\t\t  "
             << processes[i].turnAroundTime << endl;
    }

    cout << "\nAverage waiting time = "
         << (float)totalWaitingTime / processes.size();
    cout << "\nAverage turn around time = "
         << (float)totalTurnAroundTime / processes.size();
}

int main() {
    vector<Process> processes = {
        {1, 10, 3},
        {2, 1, 1},
        {3, 2, 4},
        {4, 1, 5},
        {5, 5, 2}
    };

    sort(processes.begin(), processes.end(), compare);

    cout << "Order of processes based on priority (higher number means higher priority):\n";
    for (const auto& process : processes) {
        cout << "Process ID: " << process.pid << ", Priority: " << process.priority << endl;
    }

    findAvgTime(processes);

    return 0;
}
