#include "test_runner.h"
#include "profile.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>
#include <list>
#include <deque>


using namespace std;

template <typename Iterator>
void PrintRange(Iterator first, Iterator last) {
	for (auto i = first; i != last; ++i) 
		cout << *i << ' ';
	cout << '\n';
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
	//list<typename RandomIt::value_type> pool;
	vector<typename RandomIt::value_type> pool;
	for (auto it = first; it != last; it++) {
		pool.push_back(move(*it));
	}
	auto cur_pos = pool.begin();
	size_t i_cur_pos = 0;
	//size_t i_cur_pos = 0;
	while (!pool.empty()) {
		*(first++) = move(*cur_pos);
		pool.erase(cur_pos);
		if (pool.empty()) {
			break;
		}
		//i_cur_pos = (i_cur_pos + step_size - 1) % pool.size();
		//cur_pos = shif_iterator(pool.begin(), i_cur_pos);
		i_cur_pos = (i_cur_pos + step_size - 1) % pool.size();
		cur_pos = pool.begin() + i_cur_pos;
	}
}

vector<int> MakeTestVector() {
	vector<int> numbers(10);
	iota(begin(numbers), end(numbers), 0);
	return numbers;
}

struct NoncopyableInt {
	int value;

	NoncopyableInt(const NoncopyableInt&) = delete;
	NoncopyableInt& operator=(const NoncopyableInt&) = delete;

	NoncopyableInt(NoncopyableInt&&) = default;
	NoncopyableInt& operator=(NoncopyableInt&&) = default;
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
	/* 1	3	5	 2	  4
	 * 0   0+2 2+2 4+2%5 1+2
	 * 
	 */

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
#define SIZE 100000
	{
		vector<int> v;
		for (int i; i < SIZE; i++) {
			v.push_back(i);
		}
		LOG_DURATION("vector");
		while (!v.empty()) {
			auto i = v.begin() + v.size() / 2;
			v.erase(i);
		}
	}
	{
		deque<int> v;
		for (int i; i < SIZE; i++) {
			v.push_back(i);
		}
		LOG_DURATION("deque");
		while (!v.empty()) {
			auto i = v.begin() + v.size() / 2;
			v.erase(i);
		}
	}
	return 0;
}
