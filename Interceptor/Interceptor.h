#pragma once

#include <iostream>


class Interceptor
{
  Interceptor() = default;

public:

  static Interceptor& get_instance() {
    static Interceptor instance;
    return instance;
  }

  void on_call() {
    std::cout << "Hi!\n";
  }

};

extern"C" void on_enter(const void* pa) {
  Interceptor::get_instance().on_call();
}
