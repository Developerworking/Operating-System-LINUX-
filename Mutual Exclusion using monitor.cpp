#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class Monitor {
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool in_use;

public:
    Monitor() : in_use(false) {}

    void enter() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !in_use; });
        in_use = true;
    }

    void leave() {
        std::unique_lock<std::mutex> lock(mtx);
        in_use = false;
        cv.notify_one();
    }
};

Monitor monitor;

void critical_section(int id) {
    monitor.enter();
    std::cout << "Thread " << id << " entering critical section.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " leaving critical section.\n";
    monitor.leave();
}

void thread_function(int id) {
    for (int i = 0; i < 5; ++i) {
        critical_section(id);
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(thread_function, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
