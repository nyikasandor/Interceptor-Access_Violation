#pragma once

#include <iostream>
#include <mutex>
#include <vector>

class Interceptor
{
  Interceptor() { std::cout << "Interceptor::Ctor" << std::endl; };
  ~Interceptor() { std::cout << "Interceptor::~Dtor" << std::endl; };

  std::mutex cout_mutex;
public:


  static Interceptor& get_instance() {
    static Interceptor instance;
    return instance;
  }

  void on_call(const void* pa) {
    static std::vector<const void*> vec;
    //vec.push_back(pa);
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "Intercepted: " << pa << '\n';
  }

};

extern"C" void on_enter(const void* pa) {
  Interceptor::get_instance().on_call(pa);
}
