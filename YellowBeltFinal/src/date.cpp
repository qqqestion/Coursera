#include "date.h"
#include <iostream>


Date::Date(const int &year_, const int &month_, const int &day_) : year(year_), month(month_), day(day_){}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const{
    return month;
}

int Date::GetDay() const{
    return day;
}

ostream& operator<<(std::ostream& stream, const Date& date){
    stream << setw(4) << setfill('0') << date.GetYear() << '-' <<
           setw(2) << setfill('0') << date.GetMonth() << '-' << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

tuple<int, int, int> MakeTupke (const Date& date){
    return make_tuple(date.GetYear(), date.GetMonth(), date.GetDay());
}

bool operator< (const Date& rhs, const Date& lhs){
    return MakeTupke(rhs) < MakeTupke(lhs);
}

bool operator<= (const Date& rhs, const Date& lhs){
    return MakeTupke(rhs) <= MakeTupke(lhs);
}

bool operator> (const Date& rhs, const Date& lhs){
    return MakeTupke(rhs) > MakeTupke(lhs);
}

bool operator>= (const Date& rhs, const Date& lhs){
    return MakeTupke(rhs) >= MakeTupke(lhs);
}

bool operator== (const Date& rhs, const Date& lhs){
    return MakeTupke(rhs) == MakeTupke(lhs);
}

bool operator!= (const Date& rhs, const Date& lhs){
    return MakeTupke(rhs) != MakeTupke(lhs);
}

Date ParseDate(istream& input){
    string line;
    input >> line;
    istringstream in(line);
    bool ok = true;

    int year;
    ok = (ok && (in >> year)) && (in.peek() == '-');
    in.ignore(1);

    int month;
    ok = ok && (in >> month) && (in.peek() == '-');
    in.ignore(1);

    int day;
    ok = ok && (in >> day);

    if (!ok){
        throw logic_error("Wrong date format: " + line);
    }
    input.ignore(1);
    return Date(year, month, day);
}
