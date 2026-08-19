#pragma once
#include <iostream>
#include<memory>
#include<vector>
#include<random>

using namespace std;

class A {
public:
	A() { cout << "A() initiated" << endl; }
	~A() { cout << "~A() called" << endl; }
};

class B {
public:
	B() { cout << "B() initiated" << endl; }
	~B() { cout << "~B() called" << endl; }
};

class Test {
	unique_ptr<A> pA{};
	B b{};
	unique_ptr<int> pInt{};
	string pStr{};
	vector<int> pArr{};
public:
	Test() { 
		cout << "Test() initiated" << endl; 
		pA.reset(new A());
		//pInt = new int;
		throw runtime_error("Failed to initialize");
		//pStr = new char[1000];
		//pArr = new int[1000];
	}
	~Test() { 
		cout << "~Test() called" << endl;
		//any exception in the destructor will terminate the program. 
		// it should be handeld within the destructor scope
		//throw runtime_error("Failed to initialize"); 
		//delete pA;
		//delete pInt;
		//delete[]pStr;
		//delete[]pArr;
	}
};

int processRecords(int count) {

	// as local variable the ~Test() called
	//Test t; 
	
	//Test() initiated
	//bad array new length, ~Test() not called.
	//Test* t = new Test(); 

	//unique_ptr<Test> t{ new Test() };

	if (count < 10) {
		throw out_of_range("Count should be greater than 10");
	}
	
	//int* p = new int[count]; // through bad_alloc exception

	//int* pArr = (int*)malloc(count * sizeof(int));
	//if (pArr == nullptr) {
	//	throw runtime_error("Failed to allocate Memory.");
	//}

	vector<int> p;
	p.reserve(count);

	vector<int> pArr;
	p.reserve(count);

	for (int i = 0; i < count; ++i) {
		pArr.push_back(i);
	}

	default_random_engine eng;
	bernoulli_distribution b_dist;
	int error_count{0};
	for (int i = 0; i < count; ++i) {
		try {
			cout << "Processing record # : " << i;
			if (!b_dist(eng)) {
				++error_count;
				throw runtime_error("Failed to process record ... -===--");
			}
			cout << endl;
		}
		catch (runtime_error& ex) {
			cout << "[ERROR: " << ex.what() << endl;
			if (error_count > 4) {
				runtime_error err("Too many errors. Aborting operation ...");
					ex = err;
					throw;
			}
		}
	}

	//free(pArr);
	//delete p;

	return 0;
}

int main() {

	try {
		Test t;
	}
	catch(runtime_error &ex){
		cout << ex.what() << endl;
	}

	return 0;
}