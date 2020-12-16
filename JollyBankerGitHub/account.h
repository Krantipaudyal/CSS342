#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<vector>
#include <string>
#include "fund.h"
//#include "binary_search_tree.h"
using namespace std;

class Account
{
public:
	//constructors and destructors
	Account();
	Account(int accNum, string acLastName, string acFirstName);
	~Account();

	//prints out history of all funds in the account 
	void fullHistory();
	//prints out the history of fund
	void fundHistory(int numFund);

	int getId() const;
	string getFirstName() const;
	string getLastName() const;

	//actions in the accountstring 
	bool Deposit(int numFund , int depAmt);
	bool Withdraw(int numFund, int withDrawAmt);
	bool Transfer(int numFund, int transferAmount, Account& toAc, int toFund);

	friend ostream& operator<< (ostream& out, Account& rhs)
	{
		out << rhs.getFirstName() << " " << rhs.getLastName() << " Account Number: " <<
			rhs.getId() << endl;
		for (int i = 0; i < rhs.ac_funds.size(); i++)
		{
			out << rhs.ac_funds[i];
		}
		return out;
	}

	//helper methods
	bool canDeposit(int fundIndex, int amt);
	bool canWithdraw(int fundIndex, int amt);
	bool canWithDrawLinked(int fundIndex, int amount);
	bool canTransfer(int fundIndex, int transAmt, Account& toAc, int toFund);

private:
	//account id
	int ac_id;
	vector<Fund> ac_funds; //different funds in a vector
	string first_name;  //ac name
	string last_name;
	//BinarySearchTree tree;
};
#endif // !ACCOUNT_H
