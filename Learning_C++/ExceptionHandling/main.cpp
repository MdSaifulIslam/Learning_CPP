#pragma once
#include <iostream>

using namespace std;

int processRecords(int count) {

	if (count < 10) {
		throw out_of_range("Count should be greater than 10");
	}
	
	int* p = new int[count]; // through bad_alloc exception

	int* pArr = (int*)malloc(count * sizeof(int));
	if (pArr == nullptr) {
		throw runtime_error("Failed to allocate Memory.");
	}
	for (int i = 0; i < count; ++i) {
		pArr[i] = i;
	}
	free(pArr);

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