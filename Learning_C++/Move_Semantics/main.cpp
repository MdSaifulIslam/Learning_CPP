#include<iostream>
#include "Integer.h"

using namespace std;

void Print(int& x) {
	cout << "Print(int& x)" << endl;
}

void Print(const int& x) {
	cout << "Print(const int& x)" << endl;
}

void Print(int&& x) {
	cout << "Print(int&& x)" << endl;
}

int main() {

	int x = 3;
	Print(x);

	Print(10);

	return 0;
}
