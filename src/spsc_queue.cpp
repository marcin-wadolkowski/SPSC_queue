#include "spsc_queue.hpp"

template<typename T>
spsc_queue<T>::spsc_queue(size_t capacity)
{
    queue = std::make_unique<std::queue<T, std::deque<T>>>();
    this->capacity = capacity;
}

template<typename T>
spsc_queue<T>::~spsc_queue()
{
    queue.reset();
}

template<typename T>
void spsc_queue<T>::push( T value ) {
    std::scoped_lock lock {producer_mutex};
    if (queue->size() < capacity)
        queue->push(value);
}

template<typename T>
T spsc_queue<T>::pop() {
    std::scoped_lock lock {consumer_mutex};
    if (queue->empty())
        throw std::out_of_range("The queue is empty");
    T front_element = queue->front();
    queue->pop();
    return front_element;
}

template<typename T>
bool spsc_queue<T>::empty() const {
    std::scoped_lock lock {producer_mutex, consumer_mutex};
    return queue->empty();
}

template<typename T>
size_t spsc_queue<T>::size() const {
    std::scoped_lock lock {producer_mutex, consumer_mutex};
    return queue->size();
}

template<typename T>
bool spsc_queue<T>::can_push() const {
    std::scoped_lock lock {producer_mutex, consumer_mutex};
    return queue->size() < capacity;
}

template class spsc_queue<int>; 
