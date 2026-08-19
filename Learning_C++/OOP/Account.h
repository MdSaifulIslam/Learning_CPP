#pragma once
#include<string>
#include<iostream>

using namespace std;

class Account {
	string m_Name;
	int m_AccNo;
	static int s_AN_Generator;

protected:
	float m_Balance;

public:
	Account(const string& name, float balance);
	~Account();

	const string getName()const;
	float getBalance()const;
	int getAccNo()const;

	void AccumulateProfit();
	void Withdraw(float amount);
	void Deposit(float amount);
	float getProfitRate()const;
};

