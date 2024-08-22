#pragma once

#ifndef __MY_DSA_VECTOR_HPP
#define __MY_DSA_VECTOR_HPP

#include <QDebug>
#include <concepts>
#include <initializer_list>
#include <new>

/// \brief concept for binary tree node type
template <typename T>
concept Comparable = requires(T const &a, T const &b) {
  { a < b } -> std::convertible_to<bool>;
  { a == b } -> std::convertible_to<bool>;
};

namespace dsa {

template <typename T> class vararray {
  using reference = T &;
  using const_reference = T const &;
  using pointer_type = T *;
  using const_pointer_type = T const *;
  using size_type = int;
  using rank_type = int;

public:
  vararray(size_type const size = 0);
  vararray(std::initializer_list<T> _list);

  void push_back(const_reference data);
  void pop_back();

  constexpr size_type size() const { return _size; };

  constexpr const_reference front() const { return _data[0]; };
  constexpr const_reference back() const { return _data[_size - 1]; };

  pointer_type begin_pointer() { return _data + 0; };
  pointer_type end_pointer() { return _data + _size - 1; };

  const_reference operator[](rank_type const idx) const {
    Q_ASSERT(idx >= 0 && idx < _size);
    return _data[idx];
  }

  reference operator[](rank_type const idx) {
    Q_ASSERT(idx >= 0 && idx < _size);
    return _data[idx];
  }

  pointer_type insert_at(rank_type const pos, const_reference data);
  bool erase_at(rank_type const pos);
  bool erase(const_reference target);

  rank_type find(const_reference target) const;

  size_type binary_search(const_reference target) const
    requires Comparable<T>;

private:
  void shrink();
  void expand();
  void realloc(size_type const new_capacity = DEFAULT_CAPACITY);

  constexpr size_type according_max_size() { return _capacity / 4 * 3; }

private:
  pointer_type _data;
  size_type _capacity = DEFAULT_CAPACITY;
  size_type _size;

  static constexpr size_type DEFAULT_CAPACITY = 5;
  static constexpr int ratio = 2;
  static constexpr int min_size_ratio = 4;
};

}; // namespace dsa

// implementation
//

namespace dsa {

template <typename T>
vararray<T>::vararray(size_type const size) : _size(size >= 0 ? size : 0) {
  _capacity =
      _size >= according_max_size(_capacity) ? _size * ratio : DEFAULT_CAPACITY;
  _data = new (std::nothrow) T;
  Q_ASSERT(_data);
  Q_ASSERT(_size >= 0);
  Q_ASSERT(_capacity >= DEFAULT_CAPACITY);
  Q_ASSERT(_size < _capacity);
}

template <typename T>
vararray<T>::vararray(std::initializer_list<T> list)
    : vararray((size_type)list.size()) {
  rank_type pos = 0;
  for (const_reference item : list) {
    _data[pos++] = item;
    Q_ASSERT(pos < _size);
  }
}

template <typename T> void vararray<T>::expand() {

  if (_size >= according_max_size()) {
    realloc(ratio * _size);
  }
}

template <typename T> void vararray<T>::shrink() {

  if (_size * min_size_ratio <= _capacity) {
    size_type const new_capacity = std::max(_size * ratio, DEFAULT_CAPACITY);
    realloc(new_capacity);
  }
}

template <typename T> void vararray<T>::realloc(size_type const new_capacity) {
  pointer_type new_data = new (std::nothrow) T[new_capacity];
  Q_ASSERT(new_data);
  for (rank_type i = 0; i < new_capacity; i++)
    new_data[i] = _data[i];
  delete _data;

  _data = new_data;
  _capacity = new_capacity;
}

template <typename T> void vararray<T>::push_back(const_reference data) {
  _size += 1;
  expand();
  _data[_size - 1] = data;
}

template <typename T> void vararray<T>::pop_back() {
  _size -= 1;
  shrink();
}

template <typename T>
vararray<T>::pointer_type vararray<T>::insert_at(const rank_type pos,
                                                 const_reference data) {
  Q_ASSERT(pos < _size && pos >= 0);

  _size += 1;
  expand();

  for (rank_type i = _size - 1; i > pos; i--) {
    _data[i] = _data[i - 1];
  }
  _data[pos] = data;
}

template <typename T> bool vararray<T>::erase_at(const rank_type pos) {
  if (pos < 0 && pos >= _size)
    return false;

  for (rank_type i = pos; i < _size - 1; i++) {
    _data[i] = _data[i + 1];
  }

  _size -= 1;
  shrink();

  return true;
}

template <typename T> bool vararray<T>::erase(const_reference target) {
  rank_type const pos = find(target);
  if (pos < 0) {
    return false;
  }

  return erase_at(pos);
}

template <typename T>
vararray<T>::rank_type vararray<T>::find(const_reference target) const {
  for (rank_type i = 0; i < _size; i++)
    if (target == _data[i])
      return i;
  return -1;
}

template <typename T>
vararray<T>::rank_type vararray<T>::binary_search(const_reference target) const
  requires Comparable<T>
{
  rank_type l = 0, r = _size;
  while (l < r) {
    rank_type const mid = (l + r) / 2;
    if (target < _data[mid]) {
      r = mid;
    } else if (target > _data[mid]) {
      l = mid;
    } else
      return mid;
  }

  return -1;
}

}; // namespace dsa

#endif
