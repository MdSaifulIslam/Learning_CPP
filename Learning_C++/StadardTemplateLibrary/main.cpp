#include <iostream>
#include <set>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <queue>
#include <map>
#include <algorithm>

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

	Programmer(const string name, int id, const string proLan) : 
		name(name),
		id(id),
		proLan(proLan){
	}

	const string & getName() const {
		return name;
	}
	const int getId() const {
		return id;
	}
	const string& getPrgrammingLanguage() const {
		return proLan;
	}

	//bool operator < (const Programmer& p) {
	//	return id < p.id;
	//}
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
}

int main() {

	AlgoSort();

	return 0;
}