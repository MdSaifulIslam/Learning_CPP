#include<iostream>
#include<sstream>
#include <cassert>
#include<initializer_list>

using namespace std;

enum class Color : long { RED = 5, GREEN, BLUE };

void FillColor(Color color) {

	if (color == Color::RED) {
		cout << "Red" << endl;
	}
	else if (color == Color::GREEN) {
		cout << "Green" << endl;
	}else if (color == Color::BLUE) {
		cout << "Blue" << endl;
	}
}

enum class TrafficLight :char { RED = 'b', GREEN, YELLOW };

class Distance {
	long double m_KMs;
public:
	Distance(long double km) : m_KMs{ km } {}
	long double getKm()const { return m_KMs; }
	void setKM(long double val_KM) { m_KMs = val_KM; }
};

Distance operator"" _mi(long double val) {
	return Distance(val * 1.6);
}

Distance operator"" _metres(long double val) {
	return Distance(val / 1000);
}

constexpr int getNumber() {
	return 42;
}

constexpr int Add(int a, int b) {
	return a + b;
}

class Bag {
	int arr[10];
	int m_size{};
public:
	Bag(initializer_list<int> vals) {
		for (auto x : vals) {
			Add(x);
		}
	}

	void Add(int val) {
		assert(m_size < 10);
		arr[m_size++] = val;
	}
	void Remove() { --m_size; }
	int& operator [](int index) { return arr[index]; } 
	/*
	//  reference to actual element — now it CAN modify by index also
	b[2] = 99;    // now works — directly modifies arr[2] inside Bag
	*/
	int getSize() const { return m_size; }
};

int main() {

	initializer_list<int> data = { 1, 2, 3, 4 };
	auto vals = { 1, 2, 3, 4, 5 };
	Bag b{ 2, 3, 4, 5 };
	b[1] = 44;
	for (int i = 0; i < b.getSize(); ++i) {
		cout << b[i] << endl; //b.operator[](i)   // what compiler translates it to — identical meaning
	}

	//constexpr int a = 9;

	///*
	//const vs constexpr:
	//1. Initialization of a const variable can be deffered until runtime
	//2. constexpr variable must be initialized at compile time
	//3. all constexpr variables are const, but not the other way round
	//4. use const to indicate the value can not be modified 
	//5. use constexpr to create expressions that can be evaluated at compile time
	//
	//*/

	//int x;
	//std::cin >> x; // User types a number at runtime

	//const int runtime_const = x;     // VALID: Value won't change after this line.
	////constexpr int compile_const = x; // ERROR: 'x' is not known at compile time.

	//// Behaves as a normal function
	//int b = getNumber();

	//// Behaves as a constexpr function
	//constexpr int c = getNumber();

	//constexpr int l = Add(2, 5); // error for Add(c, 5), it will not wait for runtime. Executed in compile time
	//int arr1[l];
	////int arr2[b]; // error as b is not const or constexpr;

	//Distance dist1{ 199.99 };
	//cout << dist1.getKm() << " KM" << endl;

	//Distance dist2{ 100.0_mi };
	//cout << dist2.getKm() << " KM" << endl;

	//Distance dist3{ 1999.0_metres };
	//cout << dist3.getKm() << " KM" << endl;

	//string s = "hello";
	//s[0] = 'W';
	//char ch = s[2];

	//cout << s << endl;
	////cin >> s;
	//cout << s.length() << endl;

	//string s1{ "hello" }, s2{ "world" };
	//s = s1 + s2;
	//s += s1;
	//cout << s << endl;

	//s.insert(6, "New Insert");
	//cout << s << endl;

	//s.erase();
	//s.clear();

	//stringstream ss;
	//int a{ 5 }, b{ 6 };
	//int sum = a + b;

	//ss << "Sum of " << a << " & " << b << " is: " << sum << endl;
	//cout << ss.str() << endl;

	//string intData = "12 15 80, abc, 77";
	//ss.str(intData);

	//while (ss >> a) {
	//	cout << a << endl; // it will print till 80;
	//}

	//Color c = Color::RED;
	//FillColor(c);
	//FillColor(Color::GREEN);
	//FillColor(static_cast<Color>(2));

	//int x = static_cast<int>(Color::RED);
	//cout << x << endl;

	//char tc = static_cast<char>(TrafficLight::RED);
	//cout << tc << endl;

	//tc = static_cast<int>(TrafficLight::RED);
	//cout << tc << endl;

	return 0;
}