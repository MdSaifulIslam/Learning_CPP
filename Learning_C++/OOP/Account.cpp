#include "Account.h"

int Account::s_AN_Generator = 100000;

Account::Account(const string& name, float balance) :
	m_Name{ name }, m_Balance{ balance } {
	m_AccNo = ++s_AN_Generator;
}

Account::~Account()
{
}

const string Account::getName() const
{
	return m_Name;
}

float Account::getBalance() const
{
	return m_Balance;
}

int Account::getAccNo() const
{
	return m_AccNo;
}

void Account::AccumulateProfit()
{
}

void Account::Withdraw(float amount) {
	if (amount < m_Balance) {
		m_Balance -= amount;
	}
	else {
		cout << "Insufficent Balance." << endl;
	}
}

void Account::Deposit(float amount) {
	m_Balance += amount;
	cout << "Updated Balance: " << m_Balance << endl;
}

float Account::getProfitRate() const {
	return 0.0f;
}
