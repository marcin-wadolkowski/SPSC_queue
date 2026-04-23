#include "spsc_queue.hpp"

int main() {
  // This is very simple example of spsc_queue usage
  spsc_queue<int> spsc_q1(10);
  int counter = 0;
  while (spsc_q1.can_push()) {
    spsc_q1.push(counter++);
  }
  while (!spsc_q1.empty()) {
    std::cout << spsc_q1.pop() << " ";
  }
  std::cout << std::endl;
  return 0;
}
