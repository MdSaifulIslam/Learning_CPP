//#include "Account.h"
#include "Saivings.h"
#include "Checking.h"
#include "Transaction.h"

int main() {

	Account* acc = new Saivings("bonb", 10000, 0.05);
	delete acc;

	Checking c_Aacc("Bob", 100);
	Transaction(&c_Aacc);

	Saivings s_Acc("Bob", 100, 0.5f);
	Transaction(&s_Acc);

	//cout << "Account No: " << acc.getAccNo() << " & Balance: " << acc.getBalance() << endl;

	//acc.Withdraw(800);
	//cout << "Account No: " << acc.getAccNo() << " & Balance: " << acc.getBalance() << endl;

	//Saivings savAcc("bob-save", 5000, 5);

	//savAcc.AccumulateProfit();
	//cout << "Account No: " << savAcc.getAccNo() << " & Balance: " << savAcc.getBalance() << endl;

	return 0;
}
