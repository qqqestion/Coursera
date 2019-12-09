#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <stdexcept>

using namespace std;

struct Date{
public:
    Date(const int& year_, const int& month_, const int& day_);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

private:
    int year;
    int month;
    int day;
};

ostream& operator<<(ostream& stream, const Date& date);

tuple<int, int, int> MakeTupke (const Date& date);

bool operator< (const Date& rhs, const Date& lhs);

bool operator<= (const Date& rhs, const Date& lhs);

bool operator> (const Date& rhs, const Date& lhs);

bool operator>= (const Date& rhs, const Date& lhs);

bool operator== (const Date& rhs, const Date& lhs);

bool operator!= (const Date& rhs, const Date& lhs);

Date ParseDate(istream& input);
