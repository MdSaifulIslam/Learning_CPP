#include<iostream>
#include "Integer.h"

using namespace std;

//Integer operator + (const Integer& a, const Integer& b) {
//	Integer temp;
//	temp.setValue(a.getValue() + b.getValue());
//	return temp;
//}

int main() {

	Integer a(1), b(3);
	Integer sum = a + b;
	sum++;
	++sum;
	cout << (sum++).getValue() << endl;
	cout << sum.getValue() << endl;
	cout << ((a == sum) == 0 ? "Not same" : "Same") << endl;

	return 0;
}
