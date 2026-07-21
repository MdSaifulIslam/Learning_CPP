#include "Integer.h"
#include<iostream>

using namespace std;

Interger::Interger()
{
	cout << "Integer()" << endl;
	m_pInt = new int(0);
}

Interger::Interger(int value)
{
	cout << "Interger(int value)" << endl;
	m_pInt = new int(value);
}

Interger::Interger(const Interger& obj)
{
	cout << "Interger(const Interger& obj)" << endl;
	m_pInt = new int(*obj.m_pInt);
}

Interger& Interger::operator=(const Interger& other)
{
	cout << "Interger::operator=(const Interger& other)" << endl;
	if (this == &other)
		return *this;

	delete m_pInt;
	m_pInt = new int(*other.m_pInt);

	return *this;
}

int Interger::getValue() const
{
	return *m_pInt;
}

void Interger::setValue(int value)
{
	*m_pInt = value;
}

Interger::~Interger()
{
	cout << "~Interger()" << endl;
	delete m_pInt;
}
