#ifndef STACK_H_
#define STACK_H_

#include "list.h"

namespace my {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() : container_(){};

  stack(std::initializer_list<value_type> const items) : container_(items) {}

  stack(const stack &s) : container_(s.container_) {}

  stack(stack &&s) { *this = std::move(s); }

  ~stack() { container_.clear(); }

  stack &operator=(const stack &s) {
    container_.clear();
    container_ = s.container_;
    return *this;
  }

  stack &operator=(stack &&s) {
    container_ = std::move(s.container_);
    return *this;
  }

  const_reference top() { return container_.back(); }

  void push(const_reference value) { container_.push_back(value); }

  bool empty() { return container_.empty(); }

  size_type size() { return container_.size(); }

  void pop() { container_.pop_back(); }

  void swap(stack &other) { container_.swap(other.container_); }

 private:
  list<T> container_;
};
}  // namespace my
#endif  // STACK_H_
