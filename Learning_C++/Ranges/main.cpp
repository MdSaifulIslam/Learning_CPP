#include <iostream>
#include <string_view>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <list>
#include <ranges>
#include <format>

using namespace std;

template<typename Container>
void Print(const Container& container, string_view message = "", string_view sep = " ") {
	cout << "#### " << (message.empty() ? "Output" : message) << " ####" << endl;
	cout << "[ ";
	string_view tab = "";
	if (sep == "\n") {
		tab = "    ";
		cout << sep;
	}
	for (auto& e : container) {
		cout << tab << e << sep;
	}
	cout << "]" << endl << endl;
}

class Programmer {

public:
	string name;
	int id;
	string proLan;

	Programmer(const string& name, int id, const string& proLan) :
		name(name),
		id(id),
		proLan(proLan) {
	}

	const string& getName() const {
		return name;
	}
	int getId() const {
		return id;
	}
	const string& getPrgrammingLanguage() const {
		return proLan;
	}
	friend ostream& operator <<(ostream& os, const Programmer& pro) {
		return os << format(
			"{:<6} {:<12} {:<6}",
			pro.id,
			pro.name,
			pro.proLan
		);
	}
};

struct ProIds {
	vector<int> ids;
	void operator()(const Programmer& p) { if (p.getPrgrammingLanguage() == "R") ids.push_back(p.getId()); }
};

void AlgoSort() {
	vector<Programmer> p1{
		Programmer{ "Afzal", 101, "c++" },
		Programmer{ "Jamil", 901, "python" },
		Programmer{ "Sajjad", 201, "R" },
		Programmer{ "Kamal", 779, "R" },
		Programmer{ "Faruk", 782, "R" },
		Programmer{ "Sakil", 109, "c++" },
		Programmer{ "Kawsar", 77, "python" },
		Programmer{ "Jamal", 78, "R" },
		Programmer{ "Firoj", 54, "R" },
		Programmer{ "Mosaddek", 41, "R" }
	};

	ranges::sort(p1, [](const auto& p1, const auto& p2) { return p1.getName() < p2.getName(); });

	Print(p1, "Sorted Programmer by name", "\n");

	int rCount{};
	rCount = ranges::count_if(p1, [](const auto& p) { return p.getPrgrammingLanguage() == "R";});
	cout << "R programmer count: " << rCount << endl;

	auto itr = ranges::find_if(p1, [](const auto& p) { return p.getPrgrammingLanguage() == "R";});
	if (itr != p1.end()) { cout << "Found : " << itr->getName() << " is a R programmar"; }
	cout << endl;

	cout << "All R programmer's name: " << endl;
	ranges::for_each(p1, [](const auto& p) { if (p.getPrgrammingLanguage() == "R") cout << " Name: " << p.getName() << endl;});

	auto rIds = ranges::for_each(p1, ProIds());

	cout << "Ids of R programmers: " << endl;
	for (int id : rIds.fun.ids) { cout << "Ids: " << id << endl; }

}

int main() {

	AlgoSort();

	//vector<int> data(20);
	//iota(data.begin(), data.end(), 20);
	//Print(data, "data");

	//random_device rd;
	//ranges::shuffle(data, rd);
	//Print(data, "Shuffeled Data");

	//ranges::sort(data);
	//Print(data, "Sorted Data");

	//list<int> dest(10);
	//auto result = ranges::copy(data.begin(), data.begin() + 5, dest.begin());
	//Print(ranges::subrange{ dest.begin(), result.out }, "Non-Zero dest");

	//ranges::for_each(dest, [](int& x) { if (x % 2 != 0) x *= 2; });
	//Print(dest, "Odd doubled");

	return 0;
}