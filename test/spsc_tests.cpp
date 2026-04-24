#include "spsc_queue.hpp"
#include <gtest/gtest.h>

TEST(spsc_queue, ten_elements) {
  spsc_queue<int> spsc_q1(10);
  int counter = 0;
  while (spsc_q1.can_push()) {
    spsc_q1.push(counter++);
  }
  EXPECT_EQ(10, spsc_q1.size());
}

TEST(spsc_queue, ten_elements_plus_one) {
  spsc_queue<int> spsc_q1(10);
  int counter = 0;
  while (spsc_q1.can_push()) {
    spsc_q1.push(counter++);
  }
  EXPECT_EQ(10, spsc_q1.size());
  // This shouldn't crash. Element will not be queued.
  spsc_q1.push(counter++);
  EXPECT_EQ(10, spsc_q1.size());
  EXPECT_EQ(0, spsc_q1.pop());
}

TEST(spsc_queue, empty) {
  spsc_queue<int> spsc_q1(1);
  EXPECT_EQ(spsc_q1.empty(), true);
  spsc_q1.push(123);
  EXPECT_EQ(spsc_q1.empty(), false);
}

TEST(spsc_queue, pop_on_empty_queue_exact_message) {
  spsc_queue<int> spsc_q1(10);
  EXPECT_EQ(0, spsc_q1.size());
  try {
    spsc_q1.pop();
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    // check if the message is exactly the same as thrown by pop() method
    EXPECT_EQ(err.what(), std::string("The queue is empty"));
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TEST(spsc_queue, pop_on_empty_queue_simple) {
  spsc_queue<int> spsc_q1(10);
  EXPECT_EQ(0, spsc_q1.size());
  EXPECT_THROW(spsc_q1.pop(), std::out_of_range);
}

// function for producer threads, used in the parallel_test
void producer(spsc_queue<int> &queue) { queue.push(0); }

// function for consumer threads, used in the parallel_test
void consumer(spsc_queue<int> &queue) { queue.pop(); }

TEST(spsc_queue, parallel_test) {
  // set capacity to 2000 elements
  spsc_queue<int> spsc_q1(2000);
  // fill queue with 1000 elements
  for (unsigned i = 0; i < 1000; ++i)
    spsc_q1.push(0);

  EXPECT_EQ(1000, spsc_q1.size());

  std::thread producers[1000];
  std::thread consumers[1000];
  // create 1000 producers and 1000 consumers
  for (int i = 0; i < 1000; i++) {
    producers[i] = std::thread(producer, std::ref(spsc_q1));
    consumers[i] = std::thread(consumer, std::ref(spsc_q1));
  }
  for (int i = 0; i < 1000; i++) {
    producers[i].join();
    consumers[i].join();
  }

  // after 1000 pushes and 1000 pops in random order there should
  // be 1000 elements in queue
  EXPECT_EQ(1000, spsc_q1.size());
}

TEST(spsc_queue, parallel_test_2) {
  // set capacity to 2000 elements
  spsc_queue<int> spsc_q1(20000);
  // fill queue with 1000 elements
  for (unsigned i = 0; i < 10000; ++i)
    spsc_q1.push(0);

  EXPECT_EQ(10000, spsc_q1.size());

  std::thread producers[10000];
  std::thread consumers[10000];
  // create 1000 producers and 1000 consumers
  for (int i = 0; i < 10000; i++) {
    producers[i] = std::thread(producer, std::ref(spsc_q1));
    consumers[i] = std::thread(consumer, std::ref(spsc_q1));
  }
  for (int i = 0; i < 10000; i++) {
    producers[i].join();
    consumers[i].join();
  }

  // after 1000 pushes and 1000 pops in random order there should
  // be 1000 elements in queue
  EXPECT_EQ(10000, spsc_q1.size());
}
