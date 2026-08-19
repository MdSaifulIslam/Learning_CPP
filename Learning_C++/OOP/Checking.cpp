#include "Checking.h"

//Checking::Checking(const string& name, float balance) : Account(name, balance) {
//
//}

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
