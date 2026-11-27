#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <queue>
#include <map>
#include <algorithm>
#include "Integer.h"
#include <fstream>
#include <filesystem>
#include <chrono>
#include <execution>
#include <random>
#include <string_view>
#include <variant>

using namespace std;

void Set(){

	multiset<int, greater<int> > s{ 8,4, 6, 7, 9, 0, 1 };
	s.insert(3);
	s.insert(3);
	s.insert(3);
	s.insert(3);
	s.insert(3);
	s.insert(8);

	auto itr = s.begin();
	while (itr != s.end()) {
		cout << *itr++ << " ";
	}

	cout << endl;

	s.erase(0);
	cout << *s.begin() + 4 << endl;

	itr = s.begin();
	while (itr != s.end()) {
		cout << *itr++ << " ";
	}

	cout << endl;

	itr = s.find(99);
	if (itr != s.end()) {
		cout << "Found" << endl;
	}
	else {
		cout << "Not found" << endl;
	}

	auto found = s.equal_range(3);
	while (found.first != found.second) {
		cout << *found.first++ << " ";
	}
}

void UnSet() {
	unordered_set<string> uset;
	uset.insert("Abdul");
	uset.insert("salam");
	uset.insert("Kamal");
	uset.insert("jabbar");
	uset.insert("barkat");
	uset.insert("rahamat");
	uset.insert("sahidul");
	uset.insert("sabbir");
	uset.insert("jamil");

	for (const auto x : uset) {
		cout << "Bucket #: " << uset.bucket(x) << " contains: " << x << endl;
	}

	    //Bucket #: 27 contains : rahamat
		//Bucket # : 51 contains : jabbar
		//Bucket # : 19 contains : Abdul
		//Bucket # : 37 contains : salam
		//Bucket # : 57 contains : Kamal
		//Bucket # : 38 contains : sabbir
		//Bucket # : 22 contains : barkat
		//Bucket # : 23 contains : sahidul
		//Bucket # : 14 contains : jamil
		//Bucket count : 64
		//Number of Elements : 9
		//Max Load Factor : 1
		//Load Factor : 0.140625

	cout << "Bucket count: " << uset.bucket_count() << endl;
	cout << "Number of Elements: " << uset.size() << endl;
	cout << "Max Load Factor: " << uset.max_load_factor() << endl;
	cout << "Load Factor: " << uset.load_factor() << endl;

}

void UnMap() {
	//unordered_map<string, string> coll;
	//coll["roll01"] = "Sabbir";
	//coll["roll02"] = "Kamal";
	//coll["roll03"] = "Sajid";
	//coll["roll04"] = "sabuh";
	//coll["roll05"] = "Subrata";

	//for (const auto& x : coll) {
	//	cout << "Bucket #: " << coll.bucket(x.first) << " -> " << x.first << " : " << x.second << endl;
	//}

	unordered_multimap<string, string> coll;
	coll.insert(make_pair("Roll01", "Sabbir"));
	coll.insert(make_pair("Roll02", "xyz"));
	coll.insert(make_pair("Roll03", "231"));
	coll.insert(make_pair("Roll01", "23434"));
	coll.insert(make_pair("Roll01", "546"));
	coll.insert(make_pair("Roll01", "567657"));

	for (const auto& x : coll) {
		cout << "Bucket #: " << coll.bucket(x.first) << " -> " << x.first << " : " << x.second << endl;
	}
}

class Employee {
public:
	string m_Name;
	int m_Id;

	Employee() = default;
	Employee(const string& name, int id) : m_Name(name), m_Id(id){}
	string getName()const { return m_Name; }
	int getId()const { return m_Id; }
};

struct EmployeeHash {
	size_t operator()(const Employee& emp)const {
		auto sName = hash<string>{}(emp.getName());
		auto sId = hash<int>{}(emp.getId());
		return sName ^ sId;
	}
};

struct EmployeeEquality {
	size_t operator()(const Employee& emp1, const Employee& emp2)const {
		return emp1.getId() == emp2.getId() && emp1.getName() == emp2.getName();
	}
};

void Hash() {
	hash<string> hash;
	cout << "Hash of Hello: " << hash("Hello") << endl;

	unordered_set<Employee, EmployeeHash, EmployeeEquality>  coll;
	coll.insert(Employee{ "Sabbir", 101 });
	coll.insert(Employee{ "Jamal", 117 });
	coll.insert(Employee{ "Kamal", 108 });
	coll.insert(Employee{ "Sabbir", 101 });
	coll.insert(Employee{ "sajjad", 1012 });

	for (const auto& x : coll) {
		cout << "Id: " << x.getId() << " Name: " << x.getName() << endl;
	}
}

void PQ() {
	cout << " Priority Queue ... " << endl;
	mt19937 engine{ random_device{}() };
	uniform_int_distribution<int> dist{ 0, 10 };
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 0; i < 10; i++) {
		auto num = dist(engine);
		cout << num << " ";
		pq.push(num);
	}
	cout << endl;

	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
}

struct stArr{
	int arr[100];
	char chArr[500];
};

void StructuredBinding() {

	//stArr sa;
	//auto [arr1, arr2] = sa; // it didn't deduce to pointer.

	Employee em{ "Abbas", 1001 };
	auto &[name, id] = em;
	id = 51;
	cout << name << " " << id << " " << em.getId() << endl;

	pair<int, int> p1{ 3, 5 };
	auto [key, value] = p1;
	cout << key << " " << value << endl;

	map<int, string> errorInfo{ { 1, "error__001" },{ 2, "error__002" }, { 3, "error__003" } };
	for (auto err : errorInfo) { cout << err.first << " " << err.second << endl; }
	for (auto [key, value] : errorInfo) { cout << key << " " << value << endl; }

	int arr[] { 1, 2, 3 };
	auto [a, b, c] = arr;
	cout << a << " " << b << " " << c << endl;


};

class Programmer {

public:
	string name;
	int id;
	string proLan;

	Programmer(const string& name, int id, const string& proLan) : 
		name(name),
		id(id),
		proLan(proLan){
	}

	const string & getName() const {
		return name;
	}
	int getId() const {
		return id;
	}
	const string& getPrgrammingLanguage() const {
		return proLan;
	}

	//bool operator < (const Programmer& p) {
	//	return id < p.id;
	//}
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
		Programmer{ "kamal", 779, "R" },
		Programmer{ "Faruk", 782, "R" }
	};


	for (auto& [name, id, proLan] : p1) {
		cout << name << " " << id << " " << proLan << endl;
	}

	sort(p1.begin(), p1.end(), [](const auto& p1, const auto& p2) { return p1.getName() < p2.getName(); });

	cout << endl << "After sorted by name ... " << endl;

	for (auto &[name, id, proLan] : p1) {
		cout << name << " " << id << " " << proLan << endl;
	}

	int rCount{};
	rCount = count_if(p1.begin(), p1.end(), [](const auto& p) { return p.getPrgrammingLanguage() == "R";});
	cout << rCount << endl;

	auto itr = find_if(p1.begin(), p1.end(), [](const auto& p) { return p.getPrgrammingLanguage() == "R";});
	if (itr != p1.end()) { cout << "Found : " << itr->getName() << " is a R programmar"; }
	cout << endl;

	for_each(p1.begin(), p1.end(), [](const auto& p) { if (p.getPrgrammingLanguage() == "R") cout << " Name: " << p.getName() << endl;});

	auto rIds = for_each(p1.begin(), p1.end(), ProIds()); 

	cout << "Ids of R programmers: " << endl;
	for (auto ids : rIds.ids) { cout << ids << endl; }

}

class Timer {
	chrono::steady_clock::time_point m_start;
public:
	Timer() :m_start{ chrono::steady_clock::now() } {};
	void showTimeDifference(string_view message = "") {
		auto end = chrono::steady_clock::now();
		auto timeDifference = end - m_start;
		cout << message
			<< ":"
			<< chrono::duration_cast<chrono::milliseconds>(timeDifference).count()
			<< endl;
	}
};

constexpr unsigned VEC_SIZE{ 1000000 };
vector<long> CreateVector() {
	vector<long> vec;
	vec.reserve(VEC_SIZE);
	default_random_engine engine{ random_device{}() };
	uniform_int_distribution<long> dist{ 0, VEC_SIZE };
	for (unsigned i = 0; i < VEC_SIZE; i++) {
		vec.push_back(dist(engine));
	}

	return vec;
}

struct Number {
	int m_Num{};
	Number(int num) : m_Num(num) { cout << __FUNCSIG__ << endl; }
	Number() { cout << __FUNCSIG__ << endl; }
	~Number() { cout << __FUNCSIG__ << endl; }
	Number(const Number& other) : m_Num(other.m_Num) { cout << __FUNCSIG__ << endl; }
	Number(Number&& other) noexcept : m_Num(other.m_Num) { cout << __FUNCSIG__ << endl; }
	Number& operator=(const Number& other) {
		cout << __FUNCSIG__ << endl;
		if (this == &other) return *this;
		m_Num = other.m_Num;
		return *this;
	}
	Number& operator=(const Number&& other) noexcept {
		cout << __FUNCSIG__ << endl;
		if (this == &other) return *this;
		m_Num = other.m_Num;
		return *this;
	}
	friend std::ostream& operator <<(std::ostream& out, const Number& n) {
		return out << n.m_Num;
	}
};

struct Modifier {
	void operator()(string& s)const { s += " modified string"; }
	void operator()(int& x)const { x += 100; }
	void operator()(Number& n)const { n.m_Num = 999; }
};
struct Visitor {
	void operator()(string& s)const { cout << "String: " << s << endl; }
	void operator()(int& x)const { cout << "Int: " << x << endl; }
	void operator()(const Number& n)const { cout << "Number: " << n << endl; }
};

int main() {

	try {
		variant<string, int, Number> v{ Number{ 10 } };
		visit(Modifier{}, v);
		visit(Visitor{}, v);
		v = "Saiful";
		visit(Modifier{}, v);
		visit(Visitor{}, v);
		auto val = get<0>(v);
		cout << val << endl;

		auto* p = get_if<string>(&v);
		cout << *p << endl;
	}
	catch(exception &ex){
		cout << "Exception: " << ex.what() << endl;
	}

	//auto dataset = CreateVector();
	//Timer t;
	//sort(execution::par, dataset.begin(), dataset.end());
	//t.showTimeDifference("Sorting time");

	//vector<Integer> vInt;
	////Integer val{ 5 };
	//////vInt.push_back(4);
	//vInt.emplace_back(1);
	//vInt.emplace_back(2);
	//vInt.emplace_back(3);
	////vInt.emplace_back(4);
	////vInt.emplace_back(5);

	//vector <pair<int, string>> data;
	//data.push_back(pair<int, string>{100, "python"});
	//data.emplace_back(100, "C++");

	//for (auto d : data) {
	//	cout << d.first << " " << d.second << endl;
	//}



	//AlgoSort();

	//ifstream input("main.cpp");
	//if (!input) {
	//	cout << "Could not open file" << endl;
	//	return -1;
	//}

	//auto size = filesystem::file_size("main.cpp");
	//cout << "size: " << size << endl;

	//string buffer;
	//buffer.resize(size);

	//input.read(buffer.data(), size);
	//cout << buffer.data() << endl;

	return 0;
}