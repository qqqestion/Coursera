#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

template <typename String>
using Group = vector<String>;

set<char> alw 	 = {'a', 'l', 'w'};
set<char> oprt   = {'o', 'p', 'r', 't'};
set<char> opt    = {'o', 'p', 't'};
set<char> alopt  = {'a', 'l', 'o', 'p', 't'};

bool isInSet(const set<char>& sets, const char letter) {
	return sets.find(letter) != sets.end();

bool isMyLetter(const char letter, char& whichSet) {
	whichSet += (isInSet(alw, letter) ? 1 : 0;
	whichSet << 1; 

	whichSet += (isInSet(oprt, letter) ? 1 : 0;
	whichSet << 1; 

	whichSet += (isInSet(opt, letter) ? 1 : 0;
	whichSet << 1; 

	whichSet += (isInSet(aropt, letter) ? 1 : 0;
	whichSet << 1; 
	if (isInSet(oprt, letter))
		whichSet = 2;
	if (isInSet(opt, letter))
		whichSet = 3;
}

vector<Group<String>> GloupHeavyStrings(vector<String> strings) {
	vector<Group<String>> result;
	for (const auto string : strings) {


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
