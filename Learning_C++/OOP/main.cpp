//#include "Account.h"
#include "Saivings.h"
#include "Checking.h"

int main() {

	Checking acc("Bob", 1000);
	cout << "Account No: " << acc.getAccNo() << " & Balance: " << acc.getBalance() << endl;

	acc.Withdraw(800);
	cout << "Account No: " << acc.getAccNo() << " & Balance: " << acc.getBalance() << endl;

	//Saivings savAcc("bob-save", 5000, 5);

	//savAcc.AccumulateProfit();
	//cout << "Account No: " << savAcc.getAccNo() << " & Balance: " << savAcc.getBalance() << endl;

	return 0;
}
