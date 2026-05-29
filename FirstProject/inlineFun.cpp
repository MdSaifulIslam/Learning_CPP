#include<iostream>
#include "inlineFun.h"

using namespace std;

inline int square(int x) {
	return x * x;
}

void inlineFun() {
	int x = 5;
	int result = square(x + 1);
	cout << result << endl;
}