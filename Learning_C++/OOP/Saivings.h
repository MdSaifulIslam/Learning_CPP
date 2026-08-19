#pragma once
#include "Account.h"
class Saivings :
    public Account {
    float m_Rate;
public:
    Saivings(const string& name, float balance, float rate);
    ~Saivings();
    float getProfitRate()const;
    void AccumulateProfit();
};

