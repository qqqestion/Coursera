#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>
#include <list>


using namespace std;

template <typename Iterator>
void PrintRange(Iterator first, Iterator last) {
	for (auto i = first; i != last; ++i) 
		cout << *i << ' ';
	cout << '\n';
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
	list<typename RandomIt::value_type*> l; 
	
	l.push_back(&(*i));
	
	auto cur_pos = first;
	
	size_t size = last - first;

	while (size) {
		l.push_back(&(*cur_pos));
		i--;

		cur_pos = first + (cur_pos - first + step_size) 

		//l.erase(cur_pos);
	}
}

vector<int> MakeTestVector() {
	vector<int> numbers(10);
	iota(begin(numbers), end(numbers), 0);
	return numbers;
}

struct NoncopyableInt {
	int value;

/*	
	NoncopyableInt(const NoncopyableInt&) = delete;
	NoncopyableInt& operator=(const NoncopyableInt&) = delete;

	NoncopyableInt(NoncopyableInt&&) = default;
	NoncopyableInt& operator=(NoncopyableInt&&) = default;
*/	
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
	return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
	return os << v.value;
}

void TestAvoidsCopying() {
	vector<NoncopyableInt> numbers;
	numbers.push_back({1});
	numbers.push_back({2});
	numbers.push_back({3});
	numbers.push_back({4});
	numbers.push_back({5});

	MakeJosephusPermutation(begin(numbers), end(numbers), 2);

	vector<NoncopyableInt> expected;
	expected.push_back({1});
	expected.push_back({3});
	expected.push_back({5});
	expected.push_back({4});
	expected.push_back({2});

	ASSERT_EQUAL(numbers, expected);
}

void MyTestAvoidsCopying() {
	vector<NoncopyableInt> numbers;
	numbers.push_back({0});
	numbers.push_back({1});
	numbers.push_back({2});
	numbers.push_back({3});
	numbers.push_back({4});
	numbers.push_back({5});
	numbers.push_back({6});
	numbers.push_back({7});
	numbers.push_back({8});
	numbers.push_back({9});

	MakeJosephusPermutation(begin(numbers), end(numbers), 3);

	vector<NoncopyableInt> expected;
	expected.push_back({0});
	expected.push_back({3});
	expected.push_back({6});
	expected.push_back({9});
	expected.push_back({4});
	expected.push_back({8});
	expected.push_back({5});
	expected.push_back({2});
	expected.push_back({7});
	expected.push_back({1});

	ASSERT_EQUAL(numbers, expected);
	for (auto& i : numbers) 
		cout << i << ' ';
	cout << "\n";
	for (auto& i : expected)
		cout << i << ' ';
	cout << "\n";
}


int main() {
	TestRunner tr;
	RUN_TEST(tr, MyTestAvoidsCopying);
	return 0;
}
