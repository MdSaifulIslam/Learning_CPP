#include<iostream>
#include "Integer.h"

using namespace std;

Integer operator + (int a, const Integer& b) {
	Integer temp;
	temp.setValue(a + b.getValue());
	return temp;
}

ostream& operator  << (ostream& out, const Integer& a) {
	out << a.getValue() << " ";
	return out;
}

istream& operator >> (istream& input, Integer& a) {
	int x;

	input >> x;
	a.setValue(x);

	return input;
}

int main() {

	Integer a(1), b(3);
	
	cin >> a;

	Integer sum1 = a + b;
	Integer sum2 = a + 5;
	Integer sum3 = 6 + a;

	cout << sum1 << sum2 << sum3 << endl;

	return 0;
}
