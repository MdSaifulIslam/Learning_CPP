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

void Store(unique_ptr<Integer> &p) {
	cout << "Storing value in a file: " << p->getValue() << endl;
}

void Operate(int value) {
	//Integer* p = GetPointer(value);
	unique_ptr<Integer> p{ GetPointer(value) };
	if (p == nullptr) {
		p.reset(new Integer{ value });
	}

	p->setValue(100);
	Display(p.get());
	//delete p;
	//p = nullptr;

	//p = new Integer{};
	p.reset(new Integer{});
	*p = __LINE__;
	Display(p.get());
	Store(p);
	*p = 200;
	//delete p;
}

int main() {

	Operate(105);

	return 0;
}
