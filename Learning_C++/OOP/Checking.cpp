#include "Checking.h"

Checking::Checking(const string& name, float balance, float m_minBalance) : 
	Account(name, balance), m_MinBalance{ m_minBalance } {

}

Checking::~Checking()
{
}

void Checking::Withdraw(float amount) {
	if ((m_Balance - amount) > 50) {
		Account::Withdraw(amount);
	}
	else {
		cout << "Invalid amount" << endl;
	}
}

float Checking::getMinBalance() const
{
	return m_MinBalance;
}
