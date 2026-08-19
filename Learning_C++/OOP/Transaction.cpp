#include "Transaction.h"

void Transaction(Account* pAcc) {
	cout << "Transaction started" << endl;
	cout << "Initial balance: " << pAcc->getBalance() << endl;

	pAcc->Deposit(100);
	pAcc->AccumulateProfit();
	pAcc->Withdraw(170);

	cout << "profit rate: " << pAcc->getProfitRate() << endl;
	cout << "Final balance: " << pAcc->getBalance() << endl;
}
