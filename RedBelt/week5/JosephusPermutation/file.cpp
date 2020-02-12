#include <iostream>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T> 
void Swap(T& t1, T& t2) {

    T temp = std::move(t1); // or T temp(std::move(t1));
    t1 = std::move(t2);
    t2 = std::move(temp);

}

template <typename RandomIt>
void Shift(RandomIt first, RandomIt last) {


	size_t size = last - first;
	
	while (size--) {
	    //*(last) = move(*(--last));
		Swap(*last, *(last - 1));
		last--;
	}

}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
	RandomIt cur_pos = first;
	RandomIt t = first;
	size_t size = last - first;

	while (size) {
		Shift(first++, cur_pos);
		
		if (!--size) {
			break;
		}
		
		size_t distance = cur_pos - first;
		cur_pos = first + (distance + step_size) % size;
	}
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}


// ÐÑ‚Ð¾ ÑÐ¿ÐµÑ†Ð¸Ð°Ð»ÑŒÐ½Ñ‹Ð¹ Ñ‚Ð¸Ð¿, ÐºÐ¾Ñ‚Ð¾Ñ€Ñ‹Ð¹ Ð¿Ð¾Ð¼Ð¾Ð¶ÐµÑ‚ Ð²Ð°Ð¼ ÑƒÐ±ÐµÐ´Ð¸Ñ‚ÑŒÑÑ, Ñ‡Ñ‚Ð¾ Ð²Ð°ÑˆÐ° Ñ€ÐµÐ°Ð»Ð¸Ð·Ð°Ñ†Ð¸Ñ
// Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ MakeJosephusPermutation Ð½Ðµ Ð²Ñ‹Ð¿Ð¾Ð»Ð½ÑÐµÑ‚ ÐºÐ¾Ð¿Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ðµ Ð¾Ð±ÑŠÐµÐºÑ‚Ð¾Ð².
// Ð¡ÐµÐ¹Ñ‡Ð°Ñ Ð²Ñ‹, Ð²Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾, Ð½Ðµ Ð¿Ð¾Ð½Ð¸Ð¼Ð°ÐµÑ‚Ðµ ÐºÐ°Ðº Ð¾Ð½ ÑƒÑÑ‚Ñ€Ð¾ÐµÐ½, Ð¾Ð´Ð½Ð°ÐºÐ¾ Ð¼Ñ‹ Ñ€Ð°ÑÑÐºÐ°Ð¶ÐµÐ¼,
// Ð¿Ð¾Ñ‡ÐµÐ¼Ñƒ Ð¾Ð½ ÑƒÑÑ‚Ñ€Ð¾ÐµÐ½ Ð¸Ð¼ÐµÐ½Ð½Ð¾ Ñ‚Ð°Ðº, Ð´Ð°Ð»ÐµÐµ Ð² Ð±Ð»Ð¾ÐºÐµ Ð¿Ñ€Ð¾ move-ÑÐµÐ¼Ð°Ð½Ñ‚Ð¸ÐºÑƒ â€”
// Ð² Ð²Ð¸Ð´ÐµÐ¾ Â«ÐÐµÐºÐ¾Ð¿Ð¸Ñ€ÑƒÐµÐ¼Ñ‹Ðµ Ñ‚Ð¸Ð¿Ñ‹Â»

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

	for (auto& i : numbers) 
		cout << i << ' ';
	cout << "\n";
	for (auto& i : expected)
		cout << i << ' ';
	cout << "\n";
}


int main() {
  
 
  MyTestAvoidsCopying();
  return 0;
}
