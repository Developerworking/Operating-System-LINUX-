#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void SCAN(std::vector<int> requests, int head, int direction, int disk_size) {
    std::vector<int> left, right;
    std::vector<int> seek_sequence;
    int seek_count = 0;

    // Add requests to left or right based on their position relative to the head
    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        if (requests[i] > head)
            right.push_back(requests[i]);
    }

    // Sort left and right vectors
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // Run the algorithm according to the initial direction
    if (direction == 0) { // Scan towards lower tracks
        // Service left side requests
        for (int i = left.size() - 1; i >= 0; i--) {
            seek_sequence.push_back(left[i]);
            seek_count += std::abs(head - left[i]);
            head = left[i];
        }
        // After reaching the beginning, if there are requests on the right, go there
        if (!right.empty()) {
            seek_sequence.push_back(0); // Go to the start of the disk
            seek_count += head;         // Distance from current position to start
            head = 0;

            for (int i = 0; i < right.size(); i++) {
                seek_sequence.push_back(right[i]);
                seek_count += std::abs(head - right[i]);
                head = right[i];
            }
        }
    } else { // Scan towards higher tracks
        // Service right side requests
        for (int i = 0; i < right.size(); i++) {
            seek_sequence.push_back(right[i]);
            seek_count += std::abs(head - right[i]);
            head = right[i];
        }
        // After reaching the end, if there are requests on the left, go there
        if (!left.empty()) {
            seek_sequence.push_back(disk_size - 1); // Go to the end of the disk
            seek_count += (disk_size - 1 - head);   // Distance from current position to end
            head = disk_size - 1;

            for (int i = left.size() - 1; i >= 0; i--) {
                seek_sequence.push_back(left[i]);
                seek_count += std::abs(head - left[i]);
                head = left[i];
            }
        }
    }

    // Print the results
    std::cout << "Seek sequence: ";
    for (int i = 0; i < seek_sequence.size(); i++) {
        std::cout << seek_sequence[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Total number of seek operations: " << seek_count << std::endl;
}

int main() {
    std::vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;   // Initial position of disk head
    int direction = 1;  // 0 for left (lower tracks), 1 for right (higher tracks)
    int disk_size = 200;

    SCAN(requests, head, direction, disk_size);

    return 0;
}
