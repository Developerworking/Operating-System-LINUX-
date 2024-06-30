#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>

sem_t mutex;

void critical_section(int id) {
    sem_wait(&mutex);
    std::cout << "Thread " << id << " entering critical section.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " leaving critical section.\n";
    sem_post(&mutex);
}

void thread_function(int id) {
    for (int i = 0; i < 5; ++i) {
        critical_section(id);
    }
}

int main() {
    sem_init(&mutex, 0, 1); // Initialize semaphore to 1

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(thread_function, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    sem_destroy(&mutex);
    return 0;
}
