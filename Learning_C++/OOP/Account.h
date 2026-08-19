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
	virtual ~Account();

	/*
	Any class that has virtual functions
	→ MUST have a virtual destructor
	
	If you ever write:  Base* ptr = new Derived{};
                    delete ptr;
	→ Base destructor MUST be virtual
	otherwise Derived destructor is silently skipped
	
	*/

	const string getName()const;
	float getBalance()const;
	int getAccNo()const;

	virtual void AccumulateProfit();
	virtual void Withdraw(float amount);
	virtual void Deposit(float amount);
	virtual float getProfitRate()const;
};

