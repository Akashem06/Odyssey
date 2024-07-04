#include "circular_buffer.hpp"
#include "gtest/gtest.h"

// Test enqueue and dequeue operations
TEST(CircularBufferQueueTest, Enqueue_Dequeue) {
    CircularBuffer<int> queue(5);
    ASSERT_EQ(queue.is_stopped(), false);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    ASSERT_EQ(queue.dequeue(), 10);
    ASSERT_EQ(queue.dequeue(), 20);

    queue.enqueue(40);
    ASSERT_EQ(queue.dequeue(), 30);

    queue.enqueue(50);
    ASSERT_EQ(queue.dequeue(), 40);
    ASSERT_EQ(queue.dequeue(), 50);
}

// Test peek operation
TEST(CircularBufferQueueTest, Peek) {
    CircularBuffer<int> queue(5);

    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    ASSERT_EQ(queue.peek(0), 100);
    ASSERT_EQ(queue.peek(1), 200);
    ASSERT_EQ(queue.peek(2), 300);
}

// Test stop operation
TEST(CircularBufferQueueTest, Stop_Buffer) {
    CircularBuffer<int> queue(5);
    ASSERT_EQ(queue.is_stopped(), false);
    queue.stop();
    ASSERT_EQ(queue.is_stopped(), true);
}