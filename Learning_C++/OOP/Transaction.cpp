#include "Transaction.h"
#include "Checking.h"

void Transaction(Account* pAcc) {
	cout << "Transaction started" << endl;
	cout << "Initial balance: " << pAcc->getBalance() << endl;

	pAcc->Deposit(100);
	pAcc->AccumulateProfit();

	Checking* pCheck = dynamic_cast<Checking*>(pAcc);
	if (pCheck != nullptr) {
		cout << "MIN Balance is: " << pCheck->getMinBalance() << endl;
	}else{
		return;
	}

	pAcc->Withdraw(170);

	cout << "profit rate: " << pAcc->getProfitRate() << endl;
	cout << "Final balance: " << pAcc->getBalance() << endl;
}

void Transaction(Account& pAcc) {
	cout << "Transaction started with ref ===== >>>>" << endl;
	cout << "Initial balance: " << pAcc.getBalance() << endl;

	pAcc.Deposit(100);
	pAcc.AccumulateProfit();

	Checking& pCheck = dynamic_cast<Checking&>(pAcc);
	cout << "MIN Balance is: " << pCheck.getMinBalance() << endl;

	pAcc.Withdraw(170);

	cout << "profit rate: " << pAcc.getProfitRate() << endl;
	cout << "Final balance: " << pAcc.getBalance() << endl;
}
