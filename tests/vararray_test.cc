#include "vararray_test.hpp"

void VararrayTest::insert_test() {
  dut.clear();
  ref.clear();

  for (int i = 0; i < N; i++) {
    int pos = (unsigned)rand() % (i + 1);
    auto const data = std::to_string(rand());

    // qDebug() << "[TEST] [" << i << "th]insert at: " << pos;
    dut.insert(pos, data);
    // qDebug() << "[TEST]insert finished" << Qt::endl;
    ref.insert(ref.begin() + pos, data);
  }

  dut.insert(dut.size(), "999");
  ref.insert(ref.end(), "999");

  qDebug() << "insert at position";
  compare();
}

void VararrayTest::erase_test() {
  // call after insert_test

  insert_test();

  for (int i = 0; i < N; i++) {
    int pos = 0;
    pos = (unsigned)rand() % ref.size();
    dut.erase_at(pos);
    ref.erase(pos + ref.begin());
  }
  qDebug() << "erase at position";
  compare();

  insert_test();
  auto nums = ref;

  for (int i = 0; i < N; i++) {
    int pos = (unsigned)rand() % nums.size();

    auto const target = nums[pos];
    nums.erase(nums.begin() + pos);

    Q_ASSERT(dut.erase(target));

    auto ref_pos = std::find(ref.begin(), ref.end(), target);
    ref.erase(ref_pos);
  }

  qDebug() << "erase with value";
  compare();
}

void VararrayTest::search_test() {
  insert_test();

  // now search
  for (int i = 0; i < N; i++) {
    int pos = (unsigned)rand() % ref.size();
    auto const target = ref[pos];
    int const find = dut.find(target);

    auto ref_pos = std::find(ref.begin(), ref.end(), target);
    Q_ASSERT(ref_pos - ref.begin() == find);
  }
  qDebug() << "search";
  compare();

  std::sort(dut.begin_pointer(), dut.end_pointer());
  std::sort(ref.begin(), ref.end());

  for (int i = 0; i < N; i++) {
    int pos = (unsigned)rand() % ref.size();
    auto const target = ref[pos];
    int const bfind = dut.binary_search(target);
    Q_ASSERT(bfind >= 0);
    Q_ASSERT(dut[bfind] == target);
    Q_ASSERT(ref[bfind] == target);
  }
  qDebug() << "binary_search";
  compare();
}

bool VararrayTest::compare() const {
  for (int i = 0; i < ref.size(); i++) {
    Q_ASSERT(dut[i] == ref[i]);
  }
  Q_ASSERT(dut.size() == ref.size());
  Q_ASSERT(dut.empty() == ref.empty());

  qDebug() << "[CORRECT]";
  return true;
}

int main() {
  srand((unsigned)time(nullptr));
  VararrayTest T1(20000);
  T1.erase_test();
  T1.search_test();
}
