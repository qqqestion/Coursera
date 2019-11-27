#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	map<set<typename String::value_type>, Group<String>> groups;
	for (String& word : strings) {
		set<typename String::value_type> chars;
		for (typename String::value_type symbol : word) {
			chars.insert(move(symbol));
		}
		groups[move(chars)].push_back(move(word));
	}
	vector<Group<String>> result;
	result.reserve(groups.size());
	for (auto& word : groups) {
		result.push_back(move(word.second));
	}
	return result;
}


void TestGroupingABC() {
	vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // ÐŸÐ¾Ñ€ÑÐ´Ð¾Ðº Ð³Ñ€ÑƒÐ¿Ð¿ Ð½Ðµ Ð¸Ð¼ÐµÐµÑ‚ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ
	ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
	ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
	
		
	vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // ÐŸÐ¾Ñ€ÑÐ´Ð¾Ðº Ð³Ñ€ÑƒÐ¿Ð¿ Ð½Ðµ Ð¸Ð¼ÐµÐµÑ‚ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ
	ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
	ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
	ASSERT_EQUAL(groups[2], vector<string>({"port"}));
	ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);
	return 0;
}

