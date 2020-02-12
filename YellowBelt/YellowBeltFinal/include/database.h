#pragma once

#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include "date.h"

class Database{
public:
    void Add(const Date& date, const string& event);

    void Print(ostream& out) const;

    template <typename Function>
    int RemoveIf (Function function);

    template <typename Function>
    vector<pair<Date, string>> FindIf (Function function) const ;

    pair<Date, string> Last(const Date& date) const ;

    void DeleteEmpty();

    void Delete(map<Date, set<string>>& deleteEvent);

private:
    map<Date, vector<string>> dates_;
    map<Date, set<string>> events_;
};

ostream& operator<<(ostream& out, const pair<Date, vector<string>>& dates);

ostream& operator<<(ostream& out, const pair<Date, string>& date);

void PrintMap(const map<Date, set<string>> map_);

template <typename Function>
int Database::RemoveIf (Function function){
    int cnt_del = 0;
    map<Date, set<string>> deletedEvent;
    for (const auto& date : dates_){
        int i = 0;
        for (string event : date.second) {
            if (function(date.first, event)) {
//                auto it = begin(dates_[date.first]) + i;
//                auto it = find(begin(dates_[date.first]), end(dates_[date.first]), event);
//                deletedEvent.push_back(*it);
                deletedEvent[date.first].insert(event);
                ++cnt_del;
                --i;
            }
            ++i;
        }
    }
    Delete(deletedEvent);
    DeleteEmpty();

    return cnt_del;
}

template <typename Function>
vector<pair<Date, string>> Database::FindIf (Function function) const {
    vector<pair<Date, string>> result;
    for (const auto& date : dates_){

        for (const string& event : date.second) {
            if (function(date.first, event)) {
                result.push_back(make_pair(date.first, event));
            }
        }

    }
    return result;
}