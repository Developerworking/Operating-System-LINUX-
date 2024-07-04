#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;    // Process ID
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void findCompletionTime(vector<Process>& processes) {
    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        current_time += process.burst_time;
        process.completion_time = current_time;
    }
}

void findTurnaroundTime(vector<Process>& processes) {
    for (auto& process : processes) {
        process.turnaround_time = process.completion_time - process.arrival_time;
    }
}

void findWaitingTime(vector<Process>& processes) {
    for (auto& process : processes) {
        process.waiting_time = process.turnaround_time - process.burst_time;
    }
}

void printProcessDetails(const vector<Process>& processes) {
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t" << process.arrival_time << "\t\t" << process.burst_time << "\t\t"
             << process.completion_time << "\t\t" << process.turnaround_time << "\t\t"
             << process.waiting_time << '\n';
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
    }

    // Sorting processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    findCompletionTime(processes);
    findTurnaroundTime(processes);
    findWaitingTime(processes);
    printProcessDetails(processes);

    return 0;
}
