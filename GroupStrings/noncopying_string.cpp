#include "noncopying_string.h"

bool NoncopyableString::value_type::operator<(const value_type oth) const {
	return value_ < oth.value_;
}

ostream& NoncopyableString::value_type::operator<<(ostream& out) const {
	out << value_;
	return out;
}

NoncopyableString::value_type NoncopyableString::value_type::operator=(const char& oth) {
	value_ = oth;
	return *this;
}

auto NoncopyableString::begin() const {
	return value;
}

auto NoncopyableString::begin() {
	return value;
}

auto NoncopyableString::end() const {
	return value[size];
}

auto NoncopyableString::end() {
	return value[size];
}

NoncopyableString::NoncopyableString(const NoncopyableString& oth) {
	copying_cnstr = oth.copying_cnstr + 1;
	memcpy(value, oth.value, sizeof(value_type) * oth.size);
	size = oth.size;
	assignment_count = oth.assignment_count;
}

NoncopyableString::NoncopyableString(const string str) {
	value = new NoncopyableString::value_type[str.size()];
	for (int i; i < str.size(); i++) {
		value[i] = str[i];
	}
	size = str.size();
}

NoncopyableString& NoncopyableString::operator=(const NoncopyableString& oth) {
	assignment_count = oth.assignment_count + 1;
	copying_cnstr = oth.copying_cnstr;
	memcpy(value, oth.value, sizeof(value_type) * oth.size);
	size = oth.size;

	return *this;
}

bool NoncopyableString::operator<(const NoncopyableString& oth) const {
	for (int i; i < size && i < oth.size ; i++) {
		if (value[i] < oth.value[i]) {
			return true;
	}
	return false;
}

/*
NoncopyableString(NoncopyableString&&) = default;
NoncopyableString& operator=(NoncopyableString&&) = default;
*/

ostream& NoncopyableString::operator<<(ostream& out) const {
	for (int i; i < size; i++) {
		out << value[i];
	}
	return out;
}

bool NoncopyableString::operator==(const NoncopyableString oth) const {
	for (int i; i < size && i < oth.size ; i++) {
		if (value[i] != oth.value[i]) {
			return false;
	}
	return true;
}
};

vector<vector<NoncopyableString>> GroupHeavyNoncopyingStrings(vector<NoncopyableString> strings) {
	map<set<NoncopyableString::value_type>, vector<NoncopyableString>> groups;
	for (NoncopyableString& word : strings) {
		set<NoncopyableString::value_type> chars;
		for (NoncopyableString::value_type symbol : word) {
			chars.insert(move(symbol));
		}
		groups[chars].push_back(move(word));
	}
	vector<vector<NoncopyableString>> result;
	for (auto& word : groups) {
		result.push_back(move(word.second));
	}
	return result;
}

