#include <iostream>
#include <thread>
#include <mutex>

std::mutex cout_mutex;

int some_func(int i) {
  std::cout << "some_func\n";
  return i*3;
}

void call_some_func() {
  for (int i = 0; i < 4e1; ++i) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    some_func(i);
  }
}

int main() {
  std::thread t1(call_some_func);
  std::thread t2(call_some_func);
  call_some_func();
  {
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "main\n";
  }

  t1.join();
  t2.join();
  return 0;
}