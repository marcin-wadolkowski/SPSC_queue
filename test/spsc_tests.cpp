#include <gtest/gtest.h>
#include "spsc_queue.hpp"

TEST(spsc_queue, ten_elements) {
    spsc_queue<int> spsc_q1(10);
    int counter = 0;
    while(spsc_q1.can_push()) {
        spsc_q1.push(counter++);
    }
    EXPECT_EQ(10, spsc_q1.size());
}

TEST(spsc_queue, ten_elements_plus_one) {
    spsc_queue<int> spsc_q1(10);
    int counter = 0;
    while(spsc_q1.can_push()) {
        spsc_q1.push(counter++);
    }
    EXPECT_EQ(10, spsc_q1.size());
    // This shouldn't crash. Element will not be queued.
    spsc_q1.push(counter++);
    EXPECT_EQ(10, spsc_q1.size());
    EXPECT_EQ(0, spsc_q1.pop());
}

TEST(spsc_queue, pop_on_empty_queue_exact_message) {
    spsc_queue<int> spsc_q1(10);
    EXPECT_EQ(0, spsc_q1.size());
    try {
        spsc_q1.pop();
        FAIL() << "Expected std::out_of_range";
    }
    catch(std::out_of_range const & err) {
        // check if the message is exactly the same as thrown by pop() method
        EXPECT_EQ(err.what(),std::string("The queue is empty"));
    }
    catch(...) {
        FAIL() << "Expected std::out_of_range";
    }
}

TEST(spsc_queue, pop_on_empty_queue_simple) {
    spsc_queue<int> spsc_q1(10);
    EXPECT_EQ(0, spsc_q1.size());
    EXPECT_THROW(spsc_q1.pop(), std::out_of_range);
}

