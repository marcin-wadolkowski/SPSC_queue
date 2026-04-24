#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <queue>

#ifndef CONTAINER
#define CONTAINER deque
#endif

template <typename T> class spsc_queue final {
private:
  size_t capacity;
  std::unique_ptr<std::queue<T, std::CONTAINER<T>>> queue;
  mutable std::mutex
      producer_mutex; // mutable because of presence in const methods
  mutable std::mutex consumer_mutex;

public:
  spsc_queue() = delete; // The queue must be bounded.
  spsc_queue(size_t capacity);
  ~spsc_queue();

  void push(T value);
  T pop(); // The pop method returns first element and then does pop
  bool empty() const;
  size_t size() const;
  bool can_push() const; // Returns true if new element can be pushed
};
