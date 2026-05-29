#include<iostream>
#include "constRef.h"

void Print(const int& ref) {
	cout << "ref is : " << ref << endl;

	// assignments
	int x = 5;
	const int MAX = 12;
	int& ref_x1 = x;
	const int& ref_x2 = x;
	ref_x1 = 20;
	x = 40;
	// ref_x2 = 22;
	cout << "ref_x1 : " << ref_x1 << ", x : " << x  << ", ref_2 : " << ref_x2 << endl;

	const int* ptr1 = &x;
	int* const ptr2 = &x;
	const int* const ptr3 = &x;
	x = 33;
	cout << "ptr1 : " << *ptr1 << ", ptr2 : " << *ptr2 << ", ptr3 : " << *ptr3 << endl;

	x = 77;
	*ptr2 = 55;
	ref_x1 = 99;
	/*
	One modifiable l-value/ non-const pointer or ref might change the whole senario, 
	whether remining all are strictly const ref, pointer or variable or not.

	For the case it is mendatory to declare variable as const: const int x = 5;
	*/
	cout << "ptr1 : " << *ptr1 << ", ptr2 : " << *ptr2 << ", ptr3 : " << *ptr3 << endl;

	cout << "ref_x1 : " << ref_x1 << ", x : " << x << ", ref_2 : " << ref_x2 << endl;
	//ref_x2 = 23;

	//const int* ptr3 = &MAX;
	//int* ptr4 = &MAX; const can not be rvalue of non-const

	const int& r1 = ref_x1;
	// int& r2 = ref_x2; const can not be rvalue of non-const

	const int*& p_ref1 = ptr1;
	int *const  p_ref2 = ptr2;

}