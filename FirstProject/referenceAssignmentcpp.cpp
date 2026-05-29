//#include<iostream>
//#include "referenceAssignment.h"
//
//using namespace std;
//
//void add(int a, int b, int& ref) {
//	ref = a + b;
//}
//
//void fact(int a, int& ref) {
//	ref = 1;
//	while (a > 1)
//		ref *= a--;
//}
//
//void swap(int& a, int& b) {
//	a = a + b;
//	b = a - b;
//	a = a - b;
//}
//
//void runRefAssignment() {
//
//	int a = 10, b = 20,sum;
//	int& ref = sum;
//
//	add(a, b, sum);
//	cout << "ref: " << sum << endl;
//
//	int fact_sum;
//	int& fact_sum_ref = fact_sum;
//	a = 5;
//	fact(a, fact_sum);
//	cout << "ref: " << fact_sum << endl;
//
//	swap(a, b);
//	cout << "b: " << b << " a: " << a << endl;
//}
//
//int& fun() {
//	int x = 30;
//	return x;
//}