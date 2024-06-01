#include "circular_buffer.hpp"

template <typename T>
void CircularBuffer<T>::enqueue(T value) {
    // Gets mutex lock
    std::unique_lock<std::mutex> lock(mtx);

    // Waits for condition variable to be notified and count < capacity, and then locks mutex
    cv_not_full.wait(lock, [this] { return count < capacity || stop_flag; });

    if(stop_flag || count >= capacity) {
        throw std::runtime_error("Queue is full or stopped");
    }
    
    buffer[tail] = value;
    tail = (tail + 1) % capacity;
    count++;
    
    // Allows one dequeue thread to run
    cv_not_empty.notify_one();
}

template <typename T>
T CircularBuffer<T>::dequeue() {
    // Gets mutex lock
    std::unique_lock<std::mutex> lock(mtx);

    // Waits for condition variable to be notified and count > 0, and then locks mutex
    cv_not_empty.wait(lock, [this] { return count > 0 || stop_flag; });

    if (count == 0 && stop_flag) {
        throw std::runtime_error("Queue is empty or stopped");
    }

    T ret = buffer[head];
    head = (head + 1) % capacity;
    count--;

    // Allows one enqueue thread to run
    cv_not_full.notify_one();
    return ret;
}

template <typename T>
T CircularBuffer<T>::peek(size_t index) {
    std::lock_guard<std::mutex> lock(mtx); // Acquire mutex lock

    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }

    return buffer[ (head + index) % capacity];
}

template <typename T>
void CircularBuffer<T>::stop() {
    // Makes sure stop_flag is true by locking the mutex
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop_flag = true;
    }
    cv_not_empty.notify_all(); // Notify all waiting threads
    cv_not_full.notify_all(); // Notify all waiting threads
}

template <typename T>
bool CircularBuffer<T>::is_empty() const {
    return count == 0;
}

template <typename T>
bool CircularBuffer<T>::is_stopped() const {
    return stop_flag;
}

template class CircularBuffer<float>;
template class CircularBuffer<int>;