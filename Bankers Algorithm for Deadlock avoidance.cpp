#include <iostream>
#include <vector>

using namespace std;

class BankersAlgorithm {
private:
    int numProcesses;
    int numResources;
    vector<vector<int>> maximum;
    vector<vector<int>> allocation;
    vector<vector<int>> need;
    vector<int> available;

    void calculateNeed() {
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                need[i][j] = maximum[i][j] - allocation[i][j];
            }
        }
    }

    bool isSafe() {
        vector<bool> finish(numProcesses, false);
        vector<int> work = available;

        while (true) {
            bool foundProcess = false;
            for (int i = 0; i < numProcesses; i++) {
                if (!finish[i]) {
                    bool canAllocate = true;
                    for (int j = 0; j < numResources; j++) {
                        if (need[i][j] > work[j]) {
                            canAllocate = false;
                            break;
                        }
                    }
                    if (canAllocate) {
                        for (int j = 0; j < numResources; j++) {
                            work[j] += allocation[i][j];
                        }
                        finish[i] = true;
                        foundProcess = true;
                    }
                }
            }
            if (!foundProcess) {
                for (int i = 0; i < numProcesses; i++) {
                    if (!finish[i]) {
                        return false;
                    }
                }
                return true;
            }
        }
    }

public:
    BankersAlgorithm(int processes, int resources) {
        numProcesses = processes;
        numResources = resources;
        maximum.resize(numProcesses, vector<int>(numResources));
        allocation.resize(numProcesses, vector<int>(numResources));
        need.resize(numProcesses, vector<int>(numResources));
        available.resize(numResources);
    }

    void inputValues() {
        cout << "Enter the allocation matrix:\n";
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                cin >> allocation[i][j];
            }
        }

        cout << "Enter the maximum matrix:\n";
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                cin >> maximum[i][j];
            }
        }

        cout << "Enter the available resources:\n";
        for (int j = 0; j < numResources; j++) {
            cin >> available[j];
        }

        calculateNeed();
    }

    bool requestResources(int process, const vector<int>& request) {
        for (int i = 0; i < numResources; i++) {
            if (request[i] > need[process][i] || request[i] > available[i]) {
                return false;
            }
        }

        for (int i = 0; i < numResources; i++) {
            available[i] -= request[i];
            allocation[process][i] += request[i];
            need[process][i] -= request[i];
        }

        if (!isSafe()) {
            for (int i = 0; i < numResources; i++) {
                available[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }
            return false;
        }

        return true;
    }
};

int main() {
    int processes, resources;
    cout << "Enter the number of processes: ";
    cin >> processes;
    cout << "Enter the number of resources: ";
    cin >> resources;

    BankersAlgorithm ba(processes, resources);
    ba.inputValues();

    while (true) {
        int process;
        cout << "Enter the process number to request resources (or -1 to exit): ";
        cin >> process;
        if (process == -1) break;

        vector<int> request(resources);
        cout << "Enter the resource request vector:\n";
        for (int i = 0; i < resources; i++) {
            cin >> request[i];
        }

        if (ba.requestResources(process, request)) {
            cout << "Request granted.\n";
        } else {
            cout << "Request denied. It would lead to an unsafe state.\n";
        }
    }

    return 0;
}
