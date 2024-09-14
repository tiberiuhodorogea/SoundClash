#include "ThreadPool.h"

void ThreadPool::_worker_thread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _condition.wait(lock, [this] { return _stop || !_tasks.empty(); });
            if (_stop && _tasks.empty()) {
                return;
            }
            task = _tasks.front();  // Copy the task
            _tasks.pop();
        }
        task();
    }
}

ThreadPool::ThreadPool(size_t threads) : _stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        _workers.emplace_back([this] { _worker_thread(); });
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _tasks.push(task);  // Copy the task into the queue
    }
    _condition.notify_one();
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for (std::thread& worker : _workers) {
        worker.join();
    }
}
