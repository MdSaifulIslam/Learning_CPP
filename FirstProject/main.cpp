#include "auto_keyword.h"
#include "constRef.h"
#include "funcOver.h"
#include "functionPointer.h"
#include "inlineFun.h"
#include "loop.h"
#include "nameSpace.h"
#include "referenceAssignment.h"
#include<iostream>
#include<map>
#include<vector>
#include "externTest.h"

//#define squareMain(x) x*x;

/*inline*/ int squareMain(int x) {
	return x * x;
};

int& getDangling() {
	int local = 99;
	return local;
}

void overwriteStack() {
	int a = 111, b = 222, c = 333;   // these use the same stack space
	cout << "inside overwriteStack" << endl;
}

// 7. auto i nfunctions
//auto f(bool flag) {
//	if (flag) {
//		return 1;
//	}
//	else {
//		return 2; // -return 2.1 inconsistent return type;
//	}
//}
//
//auto mul(int a, double b) -> double {
//	return a * b;
//}

// 8. auto with lambda

namespace Basic {
	float cal(float a, float b) {
		return a + b;
	}
}
namespace Other {
	float cal(float a, float b) {
		return a + b;
	}
}

namespace Sort {
	void QuickSort(int* list) {
		return;
	}
	void InsertionSort(int* list) {
		return;
	}
	void MergeSort(int** list) {
		return;
	}
	namespace Comparision {
		void Less(int* list) {
			return;
		}
		void Grater(int* list) {
			return;
		}
	}
}

namespace {
	void innerFunction() {
		return;
	}
}

int main() {
	using namespace std;
	
	innerFunction();
	cout << Basic::cal(2.3f, 5.6f) << endl;
	using namespace Other;
	cout << cal(3.4f, 9.6f);
	int arr[] = {1, 2, 3, 4};
	Sort::Comparision::Grater(arr);

	functionPointer();
	//functionPointer();
	//cout << squareMain(3) << endl;
	//cout << sqrt(2.3) << endl;
	//cout << pow(2, 3) << endl;

	//int x = 5;
	//Print(x);

	//int& r = getDangling();
	//overwriteStack();

	//r = 500;

	//cout << r << endl;

	//int a = 10;
	//int b = 20;

	//const int* ptr = &a;   

	//// *ptr = 50; error   
	//ptr = &b;   
	//cout << *ptr<< endl;

	//b = 30;
	//cout << *ptr << endl;

	//int const *  ptr2;

	//int x = 10;
	//int& ref = x;

	//cout << x << " " << ref << endl;
	//cout << &x << " " << &ref << endl;

	//int y = 20;
	//ref = y;

	//cout << y << " " << x << " " << ref << endl;
	//cout << &y << " " << &x << " " << &ref << endl;

	//int a = 5, b = 10;
	//swap(a, b);

	//cout << a << " " << b << endl;


	//int factRes = 1;
	//fact(a, factRes);
	//cout << "Factorial of " << a << " is : " << factRes << endl;

	//int x = squareMain(10 +1);

	//cout << x << endl;
	// inline function


	/*Add(1, 2);
	Add(1.2f, 2);*/

	//PrintA(1);



	//loop();

	// namespcase
	//nameSpace();

	//function pointer
	//functionPointer();

	// inline Function
	//int x = 5;
	//int result = squareMain(x); // inline still not done, check later
	//cout << result << endl;
	/*int x = 5;
	int result = square(5 + x);
	cout << result << endl;

	inlineFun();*/

	//null reference 
	//fun() = 30;
	//cout << fun();

	//int* p = NULL;
	//int& ref = *p;
	//cout << ref << endl;


	// 28. auto
	/*auto_keyword();*/

	// 26. const qualifier
	//int x = 5;
	//Print(2);

	// referance assignment ->
	//runRefAssignment();
	// <- reference assignment

	// reference ->;

	//int a = 20;
	//int y = 1000;

	//int &ref = a;

	//ref = y;

	//cout << "ref: " << ref << endl;
	//cout << "a: " << a << endl;
	// <- reference;


	//uniform initializer

	//char buff[55]{'f', 'c', 'd'};
	//float f{};
	//int i{f};
	////cin.getline( buff, 1024, '\n');
	//cout << buff << ". " << i;

	//char buff[55]{ 'f', 'c', 'd' };
	//for (int i = 0; i < 55; i++) {
	//	cout << buff[i] << " > ";
	//}

	//buff[45] = 'c';

	//cout << "\n";

	//cin.getline(buff, 55, '\0');

	//for (int i = 0; i < 55; i++) {
	//	cout << buff[i] << " > ";
	//}

	//int x = 10;
	//cout << &x << endl;

	//int* ptr = nullptr;

	////cout << *ptr << endl;

	//ptr = &x;

	//cout << *ptr << endl;


	return 0;
}