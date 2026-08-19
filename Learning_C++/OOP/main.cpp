//#include "Account.h"
#include "Saivings.h"
#include "Checking.h"
#include "Transaction.h"

int main() {

	Account* acc = new Saivings("bonb", 10000, 0.05);
	delete acc;

	cout << "\n\n\n";

	Saivings s_Aac("Bob", 100, 0.01);
	try {
		Transaction(s_Aac);
	}
	catch(exception &ex){
		cout << "Excwption: " << ex.what() << endl;
	}

	cout << "\n\n\n";

	Checking s_Acc2("Bob", 100, 120);
	try {
		Transaction(s_Acc2);
	}
	catch (exception& ex) {
		cout << "Excwption: " << ex.what() << endl;
	}

	//cout << "Account No: " << acc.getAccNo() << " & Balance: " << acc.getBalance() << endl;

	//acc.Withdraw(800);
	//cout << "Account No: " << acc.getAccNo() << " & Balance: " << acc.getBalance() << endl;

	//Saivings savAcc("bob-save", 5000, 5);

	//savAcc.AccumulateProfit();
	//cout << "Account No: " << savAcc.getAccNo() << " & Balance: " << savAcc.getBalance() << endl;

	return 0;
}
