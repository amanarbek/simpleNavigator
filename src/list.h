#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include <iostream>
#include <limits>

namespace my {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  struct node {
    node *prev_;
    node *next_;
    value_type value_;

   public:
    node(node *prev = nullptr, node *next = nullptr,
         value_type value = value_type())
        : prev_(prev), next_(next), value_(value) {}
  };

  class ListIterator {
    friend class list;

   public:
    ListIterator() : iterator_(nullptr) {}

    ListIterator(node *ptr) : iterator_(ptr) {}

    value_type &operator*() { return iterator_->value_; }

    bool operator==(const ListIterator &iterator) {
      return iterator_ == iterator.iterator_;
    }

    bool operator!=(const ListIterator &iterator) {
      return iterator_ != iterator.iterator_;
    }

    ListIterator operator++(int) {
      auto tmp = iterator_;
      iterator_ = iterator_->next_;
      return tmp;
    }

    ListIterator &operator++() {
      iterator_ = iterator_->next_;
      return *this;
    }

    ListIterator &operator--() {
      iterator_ = iterator_->prev_;
      return *this;
    }

    ListIterator operator--(int) {
      auto tmp = iterator_;
      iterator_ = iterator_->prev_;
      return tmp;
    }

   private:
    node *iterator_;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator(){};
    ListConstIterator(node *ptr) : ListIterator(ptr) {}
    ListConstIterator(const ListIterator &other) : ListIterator(other) {}
    const value_type &operator*() const { return this->iterator_->value_; }
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  list() : end_node_(new node()), size_(0) {
    end_node_->prev_ = end_node_->next_ = end_node_;
  }

  list(size_type count) : list() {
    for (size_t i = 0; i < count; ++i) {
      push_back(0);
    }
  }

  list(std::initializer_list<value_type> const &items) : list() {
    for (auto item : items) {
      push_back(item);
    }
  }

  list(const list &l) : list() {
    for (const auto &item : l) {
      push_back(item);
    }
  }

  list(list &&l) : list() {
    std::swap(end_node_, l.end_node_);
    std::swap(size_, l.size_);
  }

  bool operator==(const list &other) { return end_node_ == other.end_node_; }

  ~list() {
    clear();
    delete end_node_;
  }

  list &operator=(const list &l) {
    clear();
    for (auto item : l) {
      push_back(item);
    }
    return *this;
  }

  list &operator=(list &&l) {
    clear();
    std::swap(end_node_, l.end_node_);
    std::swap(size_, l.size_);
    return *this;
  }

  const_reference front() const { return end_node_->next_->value_; }

  const_reference back() const { return end_node_->prev_->value_; }

  bool empty() const noexcept { return end_node_ == end_node_->prev_; }

  size_type size() { return size_; }

  size_type max_size() {
    return std::numeric_limits<std::ptrdiff_t>::max() / sizeof(node);
  }

  iterator insert(iterator pos, const_reference value) {
    node *tmp = new node(pos.iterator_->prev_, pos.iterator_, value);
    pos.iterator_->prev_->next_ = tmp;
    pos.iterator_->prev_ = tmp;
    ++size_;
    return tmp;
  }

  void erase(iterator pos) {
    if (end_node_->prev_ == end_node_) {
      return;
    }
    pos.iterator_->prev_->next_ = pos.iterator_->next_;
    pos.iterator_->next_->prev_ = pos.iterator_->prev_;
    delete pos.iterator_;
    --size_;
  }

  void push_front(const_reference value) { insert(end_node_->next_, value); }

  void pop_front() { erase(end_node_->next_); }

  void swap(list &other) {
    std::swap(end_node_, other.end_node_);
    std::swap(size_, other.size_);
  }

  void splice(const_iterator pos, list &other) {
    if (!other.empty()) {
      for (iterator it = other.begin(); it != other.end(); ++it) {
        insert(pos, *it);
      }
      other.clear();
    }
  }

  void merge(list &other) {
    if (this == &other) {
      return;
    }
    auto first = begin();
    auto second = other.begin();
    while (first != end() && second != other.end()) {
      if (first.iterator_->value_ < second.iterator_->value_) {
        first++;
      } else {
        moveNode(first, second++);
        --other.size_;
        ++size_;
      }
    }
    while (second != other.end()) {
      moveNode(first, second++);
      --other.size_;
      ++size_;
    }
  }

  void reverse() {
    if (size() == 1 && size() == 0) {
      return;
    }
    size_type count = 0;
    for (auto i = begin(); count <= size(); ++i) {
      count++;
      std::swap(i.iterator_->prev_, i.iterator_->next_);
    }
  }

  void unique() {
    for (auto i = begin(); i != end(); ++i) {
      if (i.iterator_->value_ == i.iterator_->next_->value_ &&
          (i.iterator_->next_ != end_node_)) {
        erase(i.iterator_->next_);
        --i;
      }
    }
  }

  void sort() {
    if (size_ <= 1) return;
    iterator i = ++begin();
    while (i != end()) {
      iterator j = i;
      --j;
      while (j != end() && *i < *j) {
        std::swap(*i, *j);
        --i;
        --j;
      }
      ++i;
    }
  }

  void moveNode(iterator first, iterator second) {
    node *tmp_first_prev = first.iterator_->prev_;
    node *tmp_first = first.iterator_;

    first.iterator_->prev_->next_ = second.iterator_;
    first.iterator_->prev_ = second.iterator_;

    second.iterator_->prev_->next_ = second.iterator_->next_;
    second.iterator_->next_->prev_ = second.iterator_->prev_;

    second.iterator_->prev_ = tmp_first_prev;
    second.iterator_->next_ = tmp_first;
    // size_++;
  }

  ListIterator begin() { return ListIterator(end_node_->next_); }

  const ListConstIterator begin() const {
    return ListConstIterator(end_node_->next_);
  }

  ListIterator end() { return ListIterator(end_node_); }

  const ListConstIterator end() const { return ListConstIterator(end_node_); }

  void push_back(const_reference value) { insert(end_node_, value); }

  void pop_back() {
    if (end_node_->prev_ == end_node_) {
      return;
    }
    if (end_node_->prev_ == end_node_->next_) {
      delete end_node_->prev_;
      end_node_->prev_ = end_node_->next_ = end_node_;
    } else {
      end_node_->prev_->prev_->next_ = end_node_;
      node *tmp = end_node_->prev_;
      end_node_->prev_ = end_node_->prev_->prev_;
      delete tmp;
    }
    --size_;
  }

  void clear() {
    while (end_node_->prev_ != end_node_) {
      pop_back();
    }
  }

 private:
  node *end_node_;
  size_type size_;
};

}  // namespace my

#endif  // LIST_H_
