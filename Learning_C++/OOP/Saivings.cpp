#include "Saivings.h"

Saivings::Saivings(const string& name, float balance, float rate): 
	Account(name, balance), m_Rate{ rate } {
}

Saivings::~Saivings()
{
}

float Saivings::getProfitRate() const{
	return m_Rate;
}

void Saivings::AccumulateProfit() {
	m_Balance += (m_Balance * m_Rate);
}
