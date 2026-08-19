#pragma once
#include "Account.h"
class Checking :
    public Account {
    float m_MinBalance;
public:
    //using Account::Account;
    Checking(const string& name, float balance, float m_minBalance);
    ~Checking();
    void Withdraw(float amount);
    float getMinBalance()const;
};

