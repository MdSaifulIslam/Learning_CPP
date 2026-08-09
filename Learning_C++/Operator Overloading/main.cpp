#include<iostream>
#include "Integer.h"
#include<memory>

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
	*a.m_pInt = x;

	return input;
}

class SmartInteger {
private:
	Integer* pInt;
public:
	explicit SmartInteger(Integer* p = nullptr) {
		pInt = p;
	}
	~SmartInteger() {
		delete pInt;
	}
	Integer* operator->() {
		return pInt;
	}
	Integer& operator*() {
		return *pInt;
	}
	SmartInteger(const SmartInteger& obj) = delete;
	SmartInteger& operator=(const SmartInteger& obj) = delete;
};

void ProcessInteger(shared_ptr<Integer> ptr) {
	cout << ptr->getValue() << endl;
}

void CreateInteger() {
	//SmartInteger p = new Integer;
	shared_ptr<Integer> p(new Integer);
	//ProcessInteger(p); // cause error, copy constructor deleted by default;
	p->setValue(5);
	ProcessInteger(p); // no error
	p->setValue(4);
	cout << (*p).getValue() << endl;
}

class Product {
	Integer p_ID;
public:
	Product(const Integer& id) :p_ID{id} {
		cout << "Product(const Integer&)" << endl;
	}
	~Product() {
		cout << "~Product()" << endl;
	}
	operator Integer() {
		return p_ID;
	}
};

int main() {

	Product p{ 5 };
	Integer id = p;
	Integer id2{ 5 };

	if (id2 == p) {
		cout << "matches" << endl;
	}

	Integer a1{ 5 };
	Integer a2 = 6;
	int x = static_cast<int>(a1);
	//int result = a1 * 77;

	//CreateInteger();

	//Integer a(1), b(3);
	//
	//cin >> a;

	//Integer sum1 = a + b;
	//Integer sum2 = a + 5;
	//Integer sum3 = 6 + a;

	//cout << sum1 << sum2 << sum3 << endl;

	return 0;
}
