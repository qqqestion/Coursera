#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

template <typename RandomIt>
void PrintRange(RandomIt range_begin, RandomIt range_end) {
	cout << "Range: ";
	for (auto i = range_begin; i != range_end; ++i) {
		cout << *i << ' ';
	}
	cout << endl;
}

void PrintTab(int tab_count) {
	for (int i = 0; i < tab_count; i++) {
		cout << '\t';
	}
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int size = range_end - range_begin;

	if (size < 2) {
		return;
	}

	vector<typename RandomIt::value_type> elements(
			range_begin, range_end
	);
	
	auto one_third = elements.begin() + size / 3;
	auto two_third = one_third + size / 3;

	MergeSort(elements.begin(), one_third);
	MergeSort(one_third, two_third);
	MergeSort(two_third, elements.end());

	vector<typename RandomIt::value_type> temp;
	merge(elements.begin(), one_third,
			one_third, two_third,
			back_inserter(temp)
	);
	merge(temp.begin(), temp.end(),
			two_third, elements.end(),
			range_begin
	);
	
}

void OneMoreTestIntVector() {
  vector<int> numbers = {9, 6, 4, 7, 8, 2, 3, 1, 5};
  MergeSort(begin(numbers), end(numbers));
  cout << numbers << endl;
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  cout << numbers << endl;
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

void Test() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
}

int main() {
  TestRunner tr;
//  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, OneMoreTestIntVector);
  RUN_TEST(tr, Test);
  return 0;
}
