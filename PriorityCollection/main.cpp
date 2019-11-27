#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>


using namespace std;

static size_t ID;
template <typename T>
class PriorityCollection {
public:
    using Id = size_t;
    using Priority = int;
#define LowestPriority 0

	PriorityCollection() : m_data(), m_priority() {}

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        m_data[ID] = make_pair(move(object), LowestPriority);
        m_priority[LowestPriority].insert(ID);
        return ID++;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        for (auto i = range_begin; i != range_end; ++i) {
            m_data[ID] = make_pair(move(*i), LowestPriority);
			*(ids_begin++) = ID;
            m_priority[LowestPriority].insert(ID++);
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return m_data.find(id) != m_data.end();
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return m_data.at(id).first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
		Priority& id_priority = m_data[id].second;
		set<Id>& set_equal_priority = m_priority[m_data[id].second];
        set_equal_priority.erase(id);
		if (set_equal_priority.empty()) {
			m_priority.erase(id_priority);
		}
		m_priority[++id_priority].insert(id);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, Priority> GetMax() const {
        return m_data.at(*(prev((*prev(m_priority.end())).second.end())));
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, Priority> PopMax() {
		Id maxs_elem_id = *prev((*prev(m_priority.end())).second.end());
		T element = move(m_data[maxs_elem_id].first);
		Priority max_priority = m_data[maxs_elem_id].second;

        pair<T, Priority> popped_elem = make_pair(move(element), max_priority);
        m_data.erase(m_data.find(maxs_elem_id));
		m_priority[max_priority].erase(maxs_elem_id);
		if (m_priority[max_priority].empty()) {
			m_priority.erase(max_priority);
		}
        return popped_elem;
    }

	//ostream& operator<<(ostream& outh, const PriorityCollection<T>& pc);
    map<Id, pair<T, Priority>> m_data;
	map<Priority, set<Id>> m_priority;
private:
// Приватные поля и методы
};

template <typename T>
ostream& operator<<(ostream& out, const PriorityCollection<T>& pc) {
	out << "data:\n" << pc.m_data;
	out << endl << "priority:\n" << pc.m_priority;
	return out;
}

class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
	cout << "Addded white_id " << strings << endl;
    const auto yellow_id = strings.Add("yellow");
	cout << "Addded yellow_id " << strings << endl;
    const auto red_id = strings.Add("red");
	cout << "Addded red_id " << strings << endl;
	strings.Get(white_id);

    strings.Promote(yellow_id);
	cout << "promoted yellow_id " << strings << endl;
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
	cout << "promoted red_id " << strings << endl;
    strings.Promote(yellow_id);
	cout << "promoted yellow_id " << strings << endl;
    {
		const auto item1 = strings.GetMax();
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
		cout << strings << endl;
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    set<int> a = {1, 2, 3, 4};
    cout << *prev(a.end()) << endl;
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
