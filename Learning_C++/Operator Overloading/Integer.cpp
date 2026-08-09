#include "Integer.h"
#include<iostream>

using namespace std;

// Default constructor
Integer::Integer()
{
	cout << "Integr()" << endl;
	m_pInt = new int(0);
}

// Parameterized constructor
Integer::Integer(int value)
{
	m_pInt = new int(value);
}

 //Copy constructor
 //we can remove, if we need to make it non-copyable
Integer::Integer(const Integer& obj)
{
	m_pInt = new int(*obj.m_pInt);
}

// Copy assignment
// we can remove, if we need to make it non-copyable
Integer& Integer::operator=(const Integer& obj)
{
	if (this == &obj)
		return *this;

	delete m_pInt;
	m_pInt = new int(*obj.m_pInt);

	return *this;
}

// Move constructor
Integer::Integer(Integer&& obj) noexcept
{
	m_pInt = obj.m_pInt;
	obj.m_pInt = nullptr;
}

//Move assignment
Integer& Integer::operator=(Integer&& obj) noexcept
{
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
	if (m_pInt == nullptr) m_pInt = new int{};
	*m_pInt = value;
}

Integer::~Integer()
{
	cout << "~Integr()" << endl;
	delete m_pInt;
}

Integer Integer::operator+(const Integer& a) const
{
	Integer temp;
	*temp.m_pInt = *m_pInt + *a.m_pInt;
	return temp;
}

Integer& Integer::operator++()
{
	++(*m_pInt);
	return *this;
}

Integer Integer::operator++(int) const
{
	Integer temp(*this); // invoke copy constructor as Integer::Integer(const Integer& obj)
	++(*m_pInt);
	return temp;
}

bool Integer::operator==(const Integer& obj) const
{
	return *m_pInt == obj.getValue(); // *m_pInt == *obj.m_pInt
}
