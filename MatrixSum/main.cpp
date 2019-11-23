#include "test_runner.h"
#include "profile.h"
#include <vector>
#include <future>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

template <typename ContainerOfVectors>
void GenerateSingleThread(
		ContainerOfVectors& result, 
		size_t first_row,
		size_t column_size
) {
	for (auto& row : result) {
		row.reserve(column_size);
		for (size_t column = 0; column < column_size; ++column) {
			row.push_back(first_row ^ column);
		}
		++first_row;
	}
}

vector<vector<int>> GenerateSingleThread(size_t size) {
	vector<vector<int>> result(size);
	GenerateSingleThread(result, 0, size);
	return result;
}

vector<vector<int>> GenerateMultiThread(
		size_t size, size_t page_size
) {
	vector<vector<int>> result(size);
	vector<future<void>> futures;
	size_t first_row = 0;
	for (auto page : Paginate(result, page_size)) {
		futures.push_back(
				async([page, first_row, size] {
					GenerateSingleThread(page, first_row, size);
				})
		);
		first_row += page_size;
	}

	return result;
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
	int64_t sum = 0;
	for (const auto& row : matrix) {
		for (auto item : row) {
			sum += item;
		}
	}
	return sum;
}

const size_t column_count = 1500;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	// Реализуйте эту функцию
	int64_t sum = 0;
	vector<future<int64_t>> futures;
	for (int i = 0; i < 9000; i += 6) {
		futures.push_back(
			  async([matrix[i]] {
				  return accumulate(begin(matrix[i]), end(matrix[i]), 0);
				  })
		);
	}
  
	return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void SpeedTest() {
	LOG_DURATION("total");
	const size_t matrix_size = 9000;
	const size_t page_size = 1500;
	{
		vector<vector<int>> matrix;
		{
			LOG_DURATION("Single thread generation");
			matrix = GenerateSingleThread(matrix_size);
		}
		{
			LOG_DURATION("Single thread sum");
			cout << SumSingleThread(matrix) << endl;
		}
	}
	{
		vector<vector<int>> matrix;
		{
			LOG_DURATION("Multi thread generation");
			matrix = GenerateMultiThread(matrix_size, page_size);
		}
		{
			LOG_DURATION("Multi thread sum");
			cout << CalculateMatrixSum(matrix) << endl;
		}
	}
}

int main() {
  TestRunner tr;
  //RUN_TEST(tr, TestCalculateMatrixSum);
  RUN_TEST(tr, SpeedTest);
}

