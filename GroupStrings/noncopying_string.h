#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;


struct NoncopyableString {
	struct value_type {
		char value_;
		int assignment_count = 0;
		int copying_cnstr = 0;

		bool operator<(const value_type oth) const ;

		ostream& operator<<(ostream& out) const;

		value_type operator=(const char& oth);
	};
	value_type *value;
	size_t size;
	int assignment_count = 0;
	int copying_cnstr = 0;

	auto begin() const;

	auto begin();

	auto end() const;

	auto end();


	NoncopyableString(const NoncopyableString& oth);

	NoncopyableString(const string str);

	NoncopyableString& operator=(const NoncopyableString& oth);

	bool operator<(const NoncopyableString& oth) const;

	/*
	NoncopyableString(NoncopyableString&&) = default;
	NoncopyableString& operator=(NoncopyableString&&) = default;
	*/

	ostream& operator<<(ostream& out) const;

	bool operator==(const NoncopyableString oth) const;
};


vector<vector<NoncopyableString>> GroupHeavyNoncopyingStrings(vector<NoncopyableString> strings);

