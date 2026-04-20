#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
    private:
        std::queue<T> queue_;
        mutable std::mutex mutex_;
        std::condition_variable m_cond ;

    public: 
    // push an element to the back of the queue (used by CAN Rx) 
    void push(const T& value) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(value);
        }
        m_cond.notify_one(); // Notify one waiting thread
    }

    // pop an element from the front of the queue (used by Processing Task)
    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        m_cond.wait(lock, [this] { return !queue_.empty(); }); // Wait until the queue is not empty
        value = queue_.front();
        queue_.pop();
        return true ;
    }
} ;

#endif 