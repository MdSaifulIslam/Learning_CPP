#include<iostream>
#include "Integer.h"

class Number {
	Integer m_Value{};
public:
	Number() = default;
	Number(int value) :m_Value(value) {
	}
	// the following copy constructor and destructor will stop or delete the move operation 
	//Number(const Number& n) : m_Value(n.m_Value) {
	//}
	//~Number() {
	//}
	
	// any kind of move implementation, copy will deleted and it creates error.
	// compiler can not create a copy and any copy assing
	//Number(Number&& n) : m_Value(std::move(n.m_Value)) {
	//}

/*
 * ==============================================================================================================
 * | Custom Provided   | Copy Constructor | Copy Assignment  | Move Constructor | Move Assignment  | Destructor |
 * ==============================================================================================================
 * | Copy constructor  | Custom           | =default         | =delete          | =delete          | =default   |
 * | Copy assignment   | =default         | Custom           | =delete          | =delete          | =default   |
 * | Move constructor  | =delete          | =delete          | Custom           | =delete          | =default   |
 * | Move assignment   | =delete          | =delete          | =delete          | Custom           | =default   |
 * | Destructor        | =default         | =default         | =delete          | =delete          | Custom     |
 * | None              | =default         | =default         | =default         | =default         | =default   |
 * ==============================================================================================================
 */


    // it works only default implementation, but it also consider as custom update, so to work, have to declare all default.
	Number(Number&& n) = default;
	Number(const Number& n) = default;
	Number& operator = (Number&&) = default;
	Number& operator = (const Number&) = default;
};

Number CreateNumber(int num) {
	Number n{ num };
	return n;
}

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

Integer Add(const Integer& a, const Integer& b) {
	Integer temp;
	temp.setValue(a.getValue() + b.getValue());
	return temp;
}

int main() {
	Number n1{ 1 };
	// copy constructor
	auto n2{ n1 };
	// copy assignment
	n2 = n1;

	// move constructor
	auto n3{ CreateNumber(3) };
	// move constructor [CreateNumber(5)] and move assignment [n3 = CreateNumber(5)]
	n3 = CreateNumber(5);

	//Integer a(1), b(3);
	//a.setValue(Add(a, b).getValue());

	//int x = 3;
	//Print(x);

	//Print(10);

	return 0;
}
