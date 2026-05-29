
#include "auto_keyword.h"
#include <iostream>

void auto_keyword() {

	/*
	auto in c++ start
	*/

	//14. When to Use auto vs When NOT To

	//vector<bool> v = { true, false, true };
	//auto val1 = v[0]; // vector<bool>::reference (proxy tpe) -not use auto
	//bool val2 = v[1];
	////v.clear(); // program crush val1 do not have access.
	//cout << val1 << " " << val2 << endl;

	// 8. auto with lambda

	//auto square = [](int x) {
	//	return x * x;
	//	};

	//auto print = [](auto x) {
	//	cout << x << endl;
	//	};

	//print("abcd");
	//print(875354);

	//cout << square(5) << endl;

	// 7. auto i nfunctions
	// 
	//f(true);
	//auto p = mul(2, 3);
	//cout << typeid(p).name() << endl;
	//6. auto in Range - Based For Loops
	//vector<int> v = { 1, 2, 3, 4, 5 };
	//for (auto x : v) {
	//	cout << x << endl;
	//	x = 45;
	//}

	//for (auto& x : v) { // auto& - REFERENCE will modifies the originals, no copy
	//	x = 77;
	//}

	//for (auto x : v) {
	//	cout << x << endl;
	//}

	//for (const auto& x : v) {
	//	cout << x << endl;
	//	//x = 88; error - const auto&
	//}

	//map<string, int> scores = { {"alice", 95}, {"bob", 87} };

	//for (pair<const string, int>& p : scores) {
	//	cout << p.first << " " << p.second << endl;
	//}

	//for (auto& p : scores) {
	//	cout << p.first << " " << p.second << endl;
	//}

	//for (const auto& [name, score] : scores) {
	//	cout << name << " " << score << endl;
	//}

	// 5. auto with pointer
	//int x = 5;
	//int* p = &x;
	//const int* cp = &x;

	//auto a = p; // int*
	//auto b = cp; // const int*
	//auto* d = p;  // same - int*
	//const auto* e = cp; // same - const int*
	//auto* c = cp; //same const int*

	//4. auto with const and &— Add Them Manually

	//int x = 5;
	//const int cx = 10;

	//// To keep reference - add & manually
	//auto& r = x;
	//auto& cr = cx;
	//r = 15;
	//cout << r << " " << x << endl;

	//// To keep both - add const& namually
	//const auto& r2 = x;
	//const auto& r3 = cx;
	////r2 = 77; // must be modifiable lvalue error

	//string name = "Afzal";
	//auto& ref = name;
	//const auto& cref = name; // best for reading


	//3. auto Drops const and References — CRITICAL RULE

	//int x = 5;
	//const int cx = 10;
	//int& ref = x;
	//const int& cr = x;

	//auto a = x; // plain copy
	//a = 77;
	//cout << &a << " " << &x << endl;

	//auto b = cx;
	//b = 99; // const DROPPED
	//cout << cx << " " << &cx << " " << b << " " << &b << endl;
	//	 
	//auto c = ref; // reference dropped
	//c = 77;
	////ref = 8;
	//cout << ref << " " << x << " " << c << endl;

	//auto d = cr; // both ref and const dropprd;
	//d = 8;
	//cout << d << " " << cr << " " << x << endl;

	//2. auto with Basic Types
	//auto x = 5;
	//x = 3.14159; // cast to 3 (int)
	//cout << x << endl;

	//auto y = 42;
	//cout << typeid(y).name() << endl;

	//auto z = 3.1459;
	//cout << typeid(z).name() << endl;

	// x = "hi"; error int != char * 

	/*
	auto in c++ end
	*/

	//auto i = 10;
	//auto j = 5;

	//auto sum = i + 4.5f;

	//static auto y = 2;

	//const int x = 44;

	//const auto var = x;
	//auto &var1 = x;
	//auto *ptr = &x;

	//auto arr = { 1, 2, 3 };

	//cout << sum << " ";

	//for ( auto & x : arr) {
	//	cout << x << " ";
	//}


}
