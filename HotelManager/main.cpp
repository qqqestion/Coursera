#include <iostream>
#include<limits.h>
#include <map>
#include <list>
#include <queue>

#include "test_runner.h"

using namespace std;
class Log {
public:
	Log(string message) {
		cout << message << " started\n";
		this->message = message;
	}
	~Log() {
		cout << message << " finished\n";
	}
private:
	string message;
};

class CurrentHoter {
public:

	CurrentHoter() : last_time(LONG_MIN), rooms(), clients(), booked_rooms(0) {}

	void check_books(int64_t time) {
		while (rooms.size() != 0 && rooms.front().first + 86399 < time) {
			booked_rooms -= rooms.front().second;
			rooms.pop();
		}
		int64_t first_time = (rooms.size() == 0) ? time : rooms.front().first;
		list<map<size_t, int64_t>::iterator> deleting_it;
		for (auto i = clients.begin(); i != clients.end(); i++) {
			if (i->second < first_time) {
				deleting_it.push_back(i);
			}
		}
		for (auto& i : deleting_it) {
			clients.erase(i);
		}
	}


	void book_rooms(int64_t time, size_t client_id, size_t room_count) {
		last_time = time;
		check_books(time);
		rooms.push({time, room_count});
		clients[client_id] = time;
		booked_rooms += room_count;
	}

	~CurrentHoter() {}
	
protected:
	int64_t last_time;
	queue<pair<int64_t, size_t>> rooms; // queue<pair<TIME, ROOMS>>
	map<size_t, int64_t> clients; // map<CLIENT_ID, LAST_TIME>
	size_t booked_rooms; // count of rooms that was booked
	friend class HotelManager;
};

class HotelManager {
public:
	HotelManager() {}

	void book(int64_t time, string hotel_name, size_t client_id, size_t room_count) {
		for (auto& hotel : all_hotels) {
			hotel.second.check_books(time);
		}
		all_hotels[hotel_name].book_rooms(time, client_id, room_count);
	}

	size_t clients(string hotel_name) {
		return all_hotels[hotel_name].clients.size();
	}

	size_t rooms(string hotel_name) {
		return all_hotels[hotel_name].booked_rooms;
	}

	~HotelManager() {}
private:
	map<string, CurrentHoter> all_hotels; // map<HOTEL_NAME, HOTES'S INF>
};

void test() {
    HotelManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.clients("mariott"), 0);
    ASSERT_EQUAL(manager.rooms("mariott"), 0);

    manager.book(0, "mariott", 1, 10);
    manager.book(0, "mariott", 2, 1);
    manager.book(0, "mariott", 3, 1);
    manager.book(0, "mariott", 4, 1);
    manager.book(0, "hilton", 1, 1);
    manager.book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.clients("mariott"), 4);
    ASSERT_EQUAL(manager.rooms("mariott"), 13);
    ASSERT_EQUAL(manager.clients("hilton"), 2);
    ASSERT_EQUAL(manager.rooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.clients("mariott"), 1);
    ASSERT_EQUAL(manager.rooms("mariott"), 1);
    ASSERT_EQUAL(manager.clients("hilton"), 1);
    ASSERT_EQUAL(manager.rooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.clients("mariott"), 2);
    ASSERT_EQUAL(manager.rooms("mariott"), 2);
    ASSERT_EQUAL(manager.clients("hilton"), 0);
    ASSERT_EQUAL(manager.rooms("hilton"), 0);
}

int main() {
	cin.tie(nullptr);

	int n;
	cin >> n;

	HotelManager hm;

	for (int i = 0; i < n; i++) {
		string command;
		cin >> command;
		if (command == "BOOK") {
			//cerr << "time	hotel_name	client_id	room_count:\n";
			int64_t time;
			string hotel_name;
			size_t client_id;
			size_t room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			cin.ignore(1);
			hm.book(time, hotel_name, client_id, room_count);
		} else if (command == "CLIENTS") {
			//cerr << "hotel_name:\n";
			string hotel_name;
			cin >> hotel_name;
			cout << hm.clients(hotel_name) << '\n';
		} else if (command == "ROOMS") {
			//cerr << "hotel_name:\n";
			string hotel_name;
			cin >> hotel_name;
			cout << hm.rooms(hotel_name) << '\n';
		}
		//cout << "command: " << command << endl;
		
	}
	
	return 0;
}
