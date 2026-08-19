#pragma once
#include <iostream>

using namespace std;

int processRecords(int count) {
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
	}
	catch(runtime_error &ex){
		cout << ex.what() << endl;
	}


	return 0;
}