#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>

template<typename T>
class spsc_queue final
{
private:
    size_t capacity;
    std::unique_ptr<std::queue<T, std::deque<T>>> queue;
    mutable std::mutex producer_mutex;
    mutable std::mutex consumer_mutex;
public:
    spsc_queue() = delete;
    spsc_queue(size_t capacity);
    ~spsc_queue();

    void push( T value );
    T pop();
    bool empty() const;
    size_t size() const;
    bool can_push() const;
};
