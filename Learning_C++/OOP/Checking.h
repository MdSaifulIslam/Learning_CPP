#pragma once
#include "Account.h"
class Checking :
    public Account {
public:
    using Account::Account;
    //Checking(const string& name, float balance);
    ~Checking();
    void Withdraw(float amount);
};

