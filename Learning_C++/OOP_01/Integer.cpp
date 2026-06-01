#include "Integer.h"

Interger::Interger()
{
	m_pInt = new int(0);
}

Interger::Interger(int value)
{
	m_pInt = new int(value);
}

Interger::Interger(const Interger& obj)
{
	m_pInt = new int(*obj.m_pInt);
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
	delete m_pInt;
}
