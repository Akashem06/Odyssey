#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>

template <typename T>
class CircularBuffer {
    private:
        std::vector<T> buffer;
        size_t head;
        size_t tail;
        size_t count;
        size_t capacity;

        std::mutex mtx;
        std::condition_variable cv_not_empty;
        std::condition_variable cv_not_full;
        bool stop_flag;

    public:
        /**
         * @brief FIFO Circular buffer
         * @param capacity size of the circular buffer
        */
        explicit CircularBuffer(size_t capacity) : buffer(capacity), head(0), tail(0), count(0), capacity(capacity), stop_flag(false) {};
        
        /**
         * @brief Adds value to the tail of the list
         * @param value to be added to the tail of the list
        */
        void enqueue(T value);

        /**
         * @brief Removes value at the head of the list
         * @returns Value at the head of the list
        */
        T dequeue();

        /**
         * @brief Checks a value at some index in the buffer
         * @param index The index in the list
         * @returns Returns the value at the index
        */
        T peek(size_t index);

        /**
         * @brief Stops all enqueing/dequeing of the buffer
        */
        void stop();

        /**
         * @brief Checks if the list is empty
         * @returns Bool of list being empty
        */
        bool is_empty() const;

        /**
         * @brief Checks if the list is stopped
         * @returns Bool of list being stopped
        */
        bool is_stopped() const;
};

#endif