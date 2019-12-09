#include "database.h"

void Database::Add(const Date& date, const string& event){
    if (events_[date].count(event) == 0) {
        dates_[date].push_back(event);
        events_[date].insert(event);
    }
}

void Database::Print(ostream& out) const {
    for (const auto& date : dates_){
        for (const string& event : date.second){
            out << date.first << " " << event << endl;
        }
    }
}

pair<Date, string> Database::Last(const Date& date) const {
    auto it = dates_.equal_range(date);
    if (it.first == it.second && it.first == begin(dates_)){
        throw invalid_argument("13");
    }
    if (it.first != begin(dates_) && it.first->first != date){
        return make_pair(prev(it.first)->first, prev(it.first)->second.back());
    }else {
        return make_pair((it.first)->first, (it.first)->second.back());
    }
}

ostream& operator<<(ostream& out, const pair<Date, string>& date){
    out << date.first << " " << date.second;
    return out;
}

ostream& operator<<(ostream& out, const pair<Date, vector<string>>& dates){
    bool flag = true;
    for (const string& i : dates.second){
        if (!flag){
            out << endl;
        }
        flag = false;
        out << dates.first << " " << i;
    }
    return out;
}

void Database::DeleteEmpty(){
    vector<Date> deleted;
    for (auto it : dates_){
        if (it.second.empty()){
            deleted.push_back(it.first);
        }
    }
    for (auto it : deleted){
        dates_.erase(it);
        events_.erase(it);
    }
}

void Database::Delete(map<Date, set<string>>& deleteEvent){
    for (auto& date : deleteEvent){
//        for (const string& event : date.second){
//            dates_[date.first].erase(event);
//            events_[date.first].erase(event);
//        }
        for (auto it = begin(deleteEvent[date.first]); it != end(deleteEvent[date.first]); ++it){
//            dates_[date.first].erase(it);
            auto it_ = find(begin(dates_[date.first]), end(dates_[date.first]), *it);
            dates_[date.first].erase(it_);
            events_[date.first].erase(*it);
        }
    }
}

void PrintMap(const map<Date, set<string>> map_){
    for (const auto& date : map_){
        bool isFirst = true, flag = true;
        for (const string& event : date.second){
            if (isFirst){
                cout << date.first << " ";
            }
            if (!flag){
                cout << ", ";
            }
            isFirst = false;
            flag = false;
            cout << event;
        }
        cout << endl;
    }
}

