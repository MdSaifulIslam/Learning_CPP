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

void Print(Integer val) {
	cout << val.getValue() << endl;
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

	// invoke the move constructor
	Integer b1{ 3 };
	auto b2{static_cast<Integer&&>(b1) };
	auto b3{ std::move(b1) };
	auto b4{ std::move(b1) };
	Print(std::move(b2));

	/*
	To set again the following change should od
	main.cpp:
		b2.setValue(5) will works, only if:
		Integer.cpp:
				void Integer::setValue(int value)
				{
					if(m_pInt == nullptr) m_pInt = new int{};
					*m_pInt = value;
				}
	*/
	b2.setValue(100);
	Print(std::move(b2));


	/*
Integer b1{ 3 };
// b1.m_pInt → [3] on heap

auto b2{ static_cast<Integer&&>(b1) };
// std::move equivalent — move constructor runs
// b2.m_pInt → [3] on heap
// b1.m_pInt → nullptr   ← b1 is now a ZOMBIE

auto b3{ std::move(b1) };
// b1.m_pInt is already nullptr
// move constructor: b3.m_pInt = nullptr, b1.m_pInt = nullptr
// b3 is also a zombie — but no crash YET (nullptr is valid to "hold")

auto b4{ std::move(b1) };
// same — b4.m_pInt = nullptr, still no crash yet

Print(std::move(b2));
// b2 still owns [3], this is fine

// printf("%d\n", b2.getValue());  ← CRASH HERE
	*/

	//printf("%d\n", b3.getValue());

	// it will crush here, b2 already moved, no reference exists except NULL:
	// printf("%d\n", b2.getValue());
	 
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
