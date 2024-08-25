/// \file
/// \brief vararray template
#pragma once

#ifndef __MY_DSA_VECTOR_HPP
#define __MY_DSA_VECTOR_HPP

#include <QDebug>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <new>

/// \brief concept for binary tree node type
template <typename T>
concept Comparable = requires(T const &a, T const &b) {
  { a < b } -> std::convertible_to<bool>;
  { a == b } -> std::convertible_to<bool>;
};

namespace dsa {

/// \brief the vararray class
template <typename T> class vararray {
  /// \brief element reference type
  using reference = T &;
  /// \brief element const reference type
  using const_reference = T const &;
  /// \brief element pointer type
  using pointer_type = T *;
  /// \brief element const pointer type
  using const_pointer_type = T const *;
  /// \brief size type. type for size and capacity
  using size_type = int;
  /// \brief size type. type for index and rank
  using rank_type = int;
  /// \brief type of the sort comparator for comparing two elements
  using sort_functor = std::function<bool(const_reference, const_reference)>;

public:
  /// \brief constructor with size and
  /// element default constructor
  /// \param size initial size of the vararray
  vararray(size_type const size = 0);
  /// \brief constructor with initializer_list
  /// \param _list initializer_list
  vararray(std::initializer_list<T> _list);
  /// \brief copy constructor
  /// \param other the object to copy
  vararray(vararray<T> const &other);

  /// \brief construct with an array with given length
  /// \param begin_pointer pointer to the array to copy
  /// \param length the length of the array to copy
  vararray(const_pointer_type begin_pointer, size_type const length);

  /// \brief destructor
  ~vararray() { delete[] _data; }

  /// \brief append an element to the end
  /// \param data the data to append
  void push_back(const_reference data);
  /// \brief pop an element from the end
  void pop_back();

  /// \brief reserve capacity for later insertion
  /// do nothing when the capacity given < actual capacity
  /// \param reserve_capacity the capacity to reserve
  void reserve(size_type const reserve_capacity);

  /// \brief get the size, readonly and noexcept
  /// \return the size of the vararray
  constexpr size_type size() const noexcept { return _size; };

  /// \brief get the capacity, readonly and noexcept
  /// \return the capacity of the vararray
  constexpr size_type capacity() const noexcept { return _capacity; };

  /// \brief check whether the vararray is empty, readonly and noexcept
  /// \return check if the vararray is empty
  constexpr bool empty() const noexcept { return !_size; }

  /// \return return the const reference of the first element
  const_reference front() const {
    Q_ASSERT(_size);
    return _data[0];
  };

  /// \return return the const reference of the last element
  const_reference back() const {
    Q_ASSERT(_size);
    return _data[_size - 1];
  };

  /// \return first pointer (&_data[0]);
  pointer_type begin_pointer() { return _data + 0; };

  /// \return last pointer (&_data[_size]);
  pointer_type end_pointer() { return _data + _size; };

  /// \brief get the element by index, readonly
  /// \param idx the index of the element
  /// \return const reference of the _data[idx];
  const_reference operator[](rank_type const idx) const {
    Q_ASSERT(idx >= 0 && idx < _size);
    return _data[idx];
  }

  /// \brief get the element by index
  /// \param idx the index of the element
  /// \return reference of the _data[idx];
  reference operator[](rank_type const idx) {
    Q_ASSERT(idx >= 0 && idx < _size);
    return _data[idx];
  }

  /// \brief assignment
  /// \return the reference of the vararray it self
  /// \param other the object to assign
  vararray<T> &operator=(vararray<T> const &other);

  /// \brief clear the vararray
  void clear();

  /// \brief sort the vararray according to the comparator
  /// \param comp the comparator to compare elements
  void sort(sort_functor comp);

  /// \brief sort the vararray with default '<'(std::less)
  void sort() requires Comparable<T>;

  /// \brief insert to the vararray at pos with data
  /// \param pos the index to insert
  /// \param data the data to insert
  /// \return the pointer to the data inserted
  pointer_type insert(rank_type const pos, const_reference data);

  /// \brief erase the element at index pos
  /// \param pos the index to delete
  /// \return return true when successfully erased
  bool erase_at(rank_type const pos);

  /// \brief erase the first element with value target
  /// \param target the target to delete
  /// \return return true when successfully erased
  bool erase(const_reference target);

  /// \brief find the first element with value target
  /// \param target the target to find
  /// \return the index of the target found; -1 when not found
  rank_type find(const_reference target) const;

  /// \brief find the element with value target
  /// require T to be Comparable and the vararray is sorted
  /// \param target the target to find
  /// \return the index of the target found; -1 when not found
  size_type binary_search(const_reference target) const requires Comparable<T>;

private:
  /// \brief shrink the capacity of the vararray
  /// used in erase/deletion
  void shrink();

  /// \brief expand the capacity of the vararray
  /// used in insert
  void expand();

  /// \brief realloc the data with new_capacity
  /// \param new_capacity the new capacity to allocate
  void realloc(size_type const new_capacity = DEFAULT_CAPACITY);

  /// \brief sort the vararray in range \[l, r) according to the comparator
  /// \param l left side of the interval, included
  /// \param r right side of the interval, not included
  /// \param comp the comparator to compare elements
  void sort_part(rank_type const l, rank_type const r, sort_functor comp);

  /// \brief partition for quick sort
  /// \param l left side of the interval, included
  /// \param r right side of the interval, not included
  /// \param comp the comparator to compare elements
  /// \return return the index of pivot point
  rank_type partition(rank_type const l, rank_type const r, sort_functor comp);

  /// \brief get the max size of the vararray with the current capacity
  /// that is we only use part of the capacity to hold elements
  /// \return return the max size
  constexpr size_type according_max_size() { return _capacity / 4 * 3; }

private:
  /// \brief the pointer to the data
  pointer_type _data;
  /// \brief store the capacity
  size_type _capacity = DEFAULT_CAPACITY;
  /// \brief store the size
  size_type _size;

  /// \brief the default capacity, also the minimal capacity
  static constexpr size_type DEFAULT_CAPACITY = 5;
  /// \brief the capacity/size should < ratio
  static constexpr int ratio = 2;
  /// \brief the capacity/size should > min_size_ratio
  static constexpr int min_size_ratio = 4;
};

}; // namespace dsa

// implementation
//

namespace dsa {

template <typename T>
vararray<T>::vararray(size_type const size) : _size(size >= 0 ? size : 0) {
  // qDebug() << "Call constructor";
  _capacity = _size >= according_max_size() ? _size * ratio : DEFAULT_CAPACITY;
  _data = new (std::nothrow) T[_capacity]{};
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
    Q_ASSERT(pos < _size);
    _data[pos++] = item;
  }
}

template <typename T> vararray<T>::vararray(vararray<T> const &other) {
  qDebug() << "Call copy constructor";

  this->_size = other.size();
  this->_capacity = _size * ratio;
  this->_data = new (std::nothrow) T[_capacity];

  Q_ASSERT(_data);

  for (rank_type i = 0; i < _size; i++) {
    _data[i] = other[i];
  }
}

template <typename T>
vararray<T>::vararray(const_pointer_type begin_pointer, size_type const length)
    : vararray(length) {
  for (size_type i = 0; i < size(); i++) {
    _data[i] = begin_pointer[i];
    Q_ASSERT(i < length);
  }
}

template <typename T>
vararray<T> &vararray<T>::operator=(vararray<T> const &other) {
  qDebug() << "Call operator=";

  delete[] this->_data;

  this->_size = other.size();
  this->_capacity = _size * ratio;
  this->_data = new (std::nothrow) T[_capacity];
  Q_ASSERT(_data);
  for (rank_type i = 0; i < _size; i++) {
    _data[i] = other[i];
  }
  return *this;
}

template <typename T> void vararray<T>::clear() {
  delete[] _data;
  _size = 0;
  _capacity = DEFAULT_CAPACITY;
  _data = new T[_capacity];
}

template <typename T> void vararray<T>::expand() {

  if (_size >= according_max_size()) {
    qDebug() << "expand with capacity: " << _capacity << " size: " << _size;
    realloc(std::max(ratio * _size, DEFAULT_CAPACITY));
  }
}

template <typename T> void vararray<T>::shrink() {

  if (_size * min_size_ratio <= _capacity) {
    size_type const new_capacity = std::max(_size * ratio, DEFAULT_CAPACITY);
    realloc(new_capacity);
  }
}

template <typename T> void vararray<T>::realloc(size_type const new_capacity) {
  qDebug() << "realloc:" << new_capacity << "with size:" << _size
           << "with capacity:" << _capacity;

  pointer_type new_data = new (std::nothrow) T[new_capacity];
  Q_ASSERT(new_data);
  for (rank_type i = 0; i < _size; i++)
    new_data[i] = _data[i];
  delete[] _data;

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

template <typename T> void vararray<T>::reserve(size_type reserve_capacity) {
  if (reserve_capacity <= _capacity)
    return;
  realloc(reserve_capacity);
}

template <typename T>
typename vararray<T>::pointer_type vararray<T>::insert(const rank_type pos,
                                              const_reference data) {
  Q_ASSERT(pos <= _size && pos >= 0);

  _size += 1;
  expand();

  for (rank_type i = _size - 1; i > pos; i--) {
    _data[i] = _data[i - 1];
  }
  _data[pos] = data;

  return _data + pos;
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
typename vararray<T>::rank_type vararray<T>::find(const_reference target) const {
  for (rank_type i = 0; i < _size; i++)
    if (target == _data[i])
      return i;
  return -1;
}

template <typename T>
typename vararray<T>::rank_type vararray<T>::binary_search(
    const_reference target) const requires Comparable<T> {
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

template <typename T>
typename vararray<T>::rank_type vararray<T>::partition(rank_type const l,
                                              rank_type const r,
                                              sort_functor comp) {
  Q_ASSERT(l >= 0 && l < size());
  Q_ASSERT(r >= 0 && r <= size());

  // auto lte = [comp](T const &a, T const &b) {
  //   return std::equal_to()(a, b) || comp(a, b);
  // };

  std::swap(_data[l], _data[l + rand() % (r - l)]);

  T const flag = _data[l];

  rank_type low = l, high = r;

  while (low < high) {
    do
      high--;
    while (low < high && comp(flag, _data[high]));

    if (low < high)
      _data[low] = _data[high];

    do
      low++;
    while (low < high && comp(_data[low], flag));

    if (low < high)
      _data[high] = _data[low];
  }

  _data[high] = flag;

  return high;
}

template <typename T>
void vararray<T>::sort_part(rank_type const l, rank_type const r,
                            sort_functor comp) {
  if (r - l < 2)
    return;
  rank_type const mid = partition(l, r, comp);
  sort_part(l, mid, comp);
  sort_part(mid + 1, r, comp);
}

template <typename T> void vararray<T>::sort(sort_functor comp) {
  sort_part(0, _size, comp);
}

template <typename T> void vararray<T>::sort() requires Comparable<T> {
  sort_part(0, _size, std::less<T>());
}

}; // namespace dsa

#endif
