#pragma once

#ifndef __TEST_VARARRAY_HPP__
#define __TEST_VARARRAY_HPP__
#include "dsa/vararray.hpp"
#include <string>
using varray = dsa::vararray<std::string>;

class VararrayTest {
public:
  VararrayTest(int const N = 10) : N(N){};
  void insert_test();
  void erase_test();
  void search_test();
  void sort_test();

private:
  bool compare() const;
  int const N;
  std::vector<std::string> ref;
  varray dut;
};

#endif
