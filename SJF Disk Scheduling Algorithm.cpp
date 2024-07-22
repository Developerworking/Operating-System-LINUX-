#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calculateTotalSeekTime(vector<int> requests, int head) {
    int totalSeekTime = 0;
    while (!requests.empty()) {
        auto it = min_element(requests.begin(), requests.end(),
                              [&head](int a, int b) {
                                  return abs(a - head) < abs(b - head);
                              });
        totalSeekTime += abs(*it - head);
        head = *it;
        requests.erase(it);
    }
    return totalSeekTime;
}

int main() {
    int n, head;
    cout << "Enter the number of requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter the request queue: ";
    for (int i = 0; i < n; ++i) {
        cin >> requests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    int totalSeekTime = calculateTotalSeekTime(requests, head);

    cout << "Total seek time: " << totalSeekTime << endl;

    return 0;
}
