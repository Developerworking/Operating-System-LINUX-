#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

void FIFOPageReplacement(int pages[], int n, int capacity) {
    unordered_set<int> s;  // To hold the pages in memory
    queue<int> indexes;    // To keep track of the order of pages

    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        // If the set has less than the capacity of frames
        if (s.size() < capacity) {
            // If the page is not present in the set
            if (s.find(pages[i]) == s.end()) {
                // Insert the page into the set
                s.insert(pages[i]);
                // Increment the page fault count
                page_faults++;
                // Push the current page into the queue
                indexes.push(pages[i]);
            }
        }
        // If the set is full
        else {
            // If the page is not present in the set
            if (s.find(pages[i]) == s.end()) {
                // Remove the first page from the queue and the set
                int val = indexes.front();
                indexes.pop();
                s.erase(val);

                // Insert the current page into the set
                s.insert(pages[i]);
                // Push the current page into the queue
                indexes.push(pages[i]);
                // Increment the page fault count
                page_faults++;
            }
        }
    }

    cout << "Total page faults: " << page_faults << endl;
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    FIFOPageReplacement(pages, n, capacity);

    return 0;
}
