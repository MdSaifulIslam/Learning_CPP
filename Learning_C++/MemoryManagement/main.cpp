#include<iostream>
#include "Integer.h"

using namespace std;

void Display(Integer* p) {
	if (!p) {
		return;
	}
	cout << p->getValue() << endl;
}

Integer* GetPointer(int value) {
	Integer* p = new Integer{value};
	return p;
}

void Operate(int value) {
	Integer* p = GetPointer(value);
	if (p == nullptr) {
		p = new Integer(value);
	}

	p->setValue(100);
	Display(p);
	delete p;
	p = nullptr;

	p = new Integer{};
	*p = __LINE__;
	Display(p);
	delete p;
}

int main() {

	Operate(105.66);

	return 0;
}
