#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {}

    int get(int key) {
        auto it = cacheItemsMap_.find(key);
        if (it == cacheItemsMap_.end()) {
            return -1;
        } else {
            cacheItemsList_.splice(cacheItemsList_.begin(), cacheItemsList_, it->second);
            return it->second->second;
        }
    }

    void put(int key, int value) {
        auto it = cacheItemsMap_.find(key);
        if (it != cacheItemsMap_.end()) {
            cacheItemsList_.splice(cacheItemsList_.begin(), cacheItemsList_, it->second);
            it->second->second = value;
            return;
        }

        if (cacheItemsList_.size() == capacity_) {
            auto del = cacheItemsList_.back();
            cacheItemsMap_.erase(del.first);
            cacheItemsList_.pop_back();
        }

        cacheItemsList_.emplace_front(key, value);
        cacheItemsMap_[key] = cacheItemsList_.begin();
    }

private:
    int capacity_;
    list<pair<int, int>> cacheItemsList_;
    unordered_map<int, list<pair<int, int>>::iterator> cacheItemsMap_;
};

int main() {
    LRUCache lruCache(2);
    lruCache.put(1, 1);
    lruCache.put(2, 2);
    cout << lruCache.get(1) << endl; // returns 1
    lruCache.put(3, 3);              // evicts key 2
    cout << lruCache.get(2) << endl; // returns -1 (not found)
    lruCache.put(4, 4);              // evicts key 1
    cout << lruCache.get(1) << endl; // returns -1 (not found)
    cout << lruCache.get(3) << endl; // returns 3
    cout << lruCache.get(4) << endl; // returns 4

    return 0;
}
