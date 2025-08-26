#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Optimized logic batch 1850
// Optimized logic batch 8851
// Optimized logic batch 8299
// Optimized logic batch 7717
// Optimized logic batch 1289
// Optimized logic batch 7896
// Optimized logic batch 5521
// Optimized logic batch 9393
// Optimized logic batch 5918
// Optimized logic batch 8377
// Optimized logic batch 5267
// Optimized logic batch 9454
// Optimized logic batch 9604
// Optimized logic batch 3719
// Optimized logic batch 3870
// Optimized logic batch 9648
// Optimized logic batch 4802
// Optimized logic batch 1953