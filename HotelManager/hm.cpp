#include <iostream>

using namespace std;

class Hotel_Manager {
public:
	Hotel_Manager() {}
	~Hotel_Manager() {}
private:
	const int SEC_DAY = 84400;
	int64_t last_time;
	queue<int64_t> timeline;

};
