#include "Integer.h"
#include<iostream>

using namespace std;

// Default constructor
Integer::Integer()
{
	cout << "Integer()" << endl;
	m_pInt = new int(0);
}

// Parameterized constructor
Integer::Integer(int value)
{
	cout << "Interger(int value)" << endl;
	m_pInt = new int(value);
}

// Copy constructor
Integer::Integer(const Integer& obj)
{
	cout << "Interger(const Interger& obj)" << endl;
	m_pInt = new int(*obj.m_pInt);
}

// Copy assignment
Integer& Integer::operator=(const Integer& obj)
{
	cout << "Interger::operator=(const Interger& other)" << endl;
	if (this == &obj)
		return *this;

	delete m_pInt;
	m_pInt = new int(*obj.m_pInt);

	return *this;
}

// Move constructor
Integer::Integer(Integer&& obj)
{
	cout << "Integer(Integer&& obj)" << endl;
	m_pInt = obj.m_pInt;
	obj.m_pInt = nullptr;
}

//Move assignment
Integer& Integer::operator=(Integer&& obj)
{
	cout << "Integer::operator=(Integer&& obj)" << endl;
	if (this == &obj)
		return *this;

	delete m_pInt;
	m_pInt = obj.m_pInt;
	obj.m_pInt = nullptr;
	return *this;
}

int Integer::getValue() const
{
	return *m_pInt;
}

void Integer::setValue(int value)
{
	*m_pInt = value;
}

Integer::~Integer()
{
	cout << "~Interger()" << endl;
	delete m_pInt;
}
