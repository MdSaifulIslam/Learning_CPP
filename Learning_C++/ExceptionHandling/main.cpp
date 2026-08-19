#pragma once
#include <iostream>
#include<memory>
#include<vector>

using namespace std;

class Test {
public:
	Test() { cout << "Test() initiated" << endl; }
	~Test() { cout << "~Test() called" << endl; }
};

int processRecords(int count) {

	// as local variable the ~Test() called
	//Test t; 
	
	//Test() initiated
	//bad array new length, ~Test() not called.
	//Test* t = new Test(); 

	unique_ptr<Test> t{ new Test() };

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

	//free(pArr);
	//delete p;

	return 0;
}

int main() {

	try {
		processRecords(numeric_limits<int>::max());
		//processRecords(5);
	}
	catch(runtime_error &ex){
		cout << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << ex.what() << endl;
	}
	catch (bad_alloc &ex) {
		cout << ex.what() << endl;
	}
	catch (exception &ex) {
		cout << ex.what() << endl;
	}
	catch (...) {
		cout << "Exception" << endl;
	}


	return 0;
}