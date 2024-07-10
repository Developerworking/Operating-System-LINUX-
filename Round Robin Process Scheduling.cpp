#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int arrivalTime;
    int completionTime;
};

void roundRobin(vector<Process>& processes, int quantum) {
    queue<Process*> processQueue;
    int currentTime = 0;
    int completedProcesses = 0;
    int n = processes.size();

    for (Process& process : processes) {
        process.remainingTime = process.burstTime;
        processQueue.push(&process);
    }

    while (completedProcesses < n) {
        Process* currentProcess = processQueue.front();
        processQueue.pop();

        if (currentProcess->remainingTime > 0) {
            if (currentProcess->remainingTime > quantum) {
                currentProcess->remainingTime -= quantum;
                currentTime += quantum;
            } else {
                currentTime += currentProcess->remainingTime;
                currentProcess->remainingTime = 0;
                currentProcess->completionTime = currentTime;
                completedProcesses++;
            }

            for (Process& process : processes) {
                if (process.arrivalTime <= currentTime && process.remainingTime > 0 && &process != currentProcess) {
                    processQueue.push(&process);
                }
            }

            if (currentProcess->remainingTime > 0) {
                processQueue.push(currentProcess);
            }
        }
    }

    cout << "Process\tBurst Time\tArrival Time\tCompletion Time" << endl;
    for (const Process& process : processes) {
        cout << "P" << process.id << "\t" << process.burstTime << "\t\t" << process.arrivalTime << "\t\t" << process.completionTime << endl;
    }
}

int main() {
    vector<Process> processes = {
        {1, 10, 0, 0, 0},
        {2, 4, 0, 1, 0},
        {3, 5, 0, 2, 0},
        {4, 6, 0, 3, 0}
    };

    int quantum = 3;
    roundRobin(processes, quantum);

    return 0;
}
