
#include "fund.h"
#include "account.h"
#include<iostream>
#include<vector>
#include<string>
#include "binary_search_tree.h"

using namespace std;

//deafult constructor for 
Account::Account()
{
	last_name = "";
	first_name = "";
	ac_id = -1;
	ac_funds.push_back(Fund("Money Market"));
	ac_funds.push_back(Fund("Prime Money Market"));
	ac_funds.push_back(Fund("Long-Term Bond"));
	ac_funds.push_back(Fund("Short-Term Bond"));
	ac_funds.push_back(Fund("500 Index Fund"));
	ac_funds.push_back(Fund("Capital Value Fund"));
	ac_funds.push_back(Fund("Growth Equity Fund"));
	ac_funds.push_back(Fund("Growth Index Fund"));
	ac_funds.push_back(Fund("Value Fund"));
	ac_funds.push_back(Fund("Stock Index Fund"));

}

//creates all the funds and sets the other data variables
Account::Account(int accNum, string acLastName, string acFirstName)
{
	ac_id = accNum;
	first_name = acFirstName;
	last_name = acLastName;

	ac_funds.push_back(Fund("Money Market"));
	ac_funds.push_back(Fund("Prime Money Market"));
	ac_funds.push_back(Fund("Long-Term Bond"));
	ac_funds.push_back(Fund("Short-Term Bond"));
	ac_funds.push_back(Fund("500 Index Fund"));
	ac_funds.push_back(Fund("Capital Value Fund"));
	ac_funds.push_back(Fund("Growth Equity Fund"));
	ac_funds.push_back(Fund("Growth Index Fund"));
	ac_funds.push_back(Fund("Value Fund"));
	ac_funds.push_back(Fund("Stock Index Fund"));
}

Account::~Account()
{
	//deafult destructor
}

//prints out full history of funds looping through the funds
void Account::fullHistory()
{
	cout << "Transaction History for: " << this->first_name << " " << this->last_name << " " << endl;
	for (int i = 0; i < ac_funds.size(); i++)
	{
		cout << this->ac_funds[i].getName() << ": $" << this->ac_funds[i].getAmount() << endl;
		this->ac_funds[i].displayHistory();
	}

}

//gives out history of indicated numfund of the fund
void Account::fundHistory(int numFund) 
{
	cout << "Transaction History for: " << this->first_name << " " << this->last_name << " " << endl;
	cout << this->ac_funds[numFund].getName() << ": $" << this->ac_funds[numFund].getAmount() << endl;
	this->ac_funds[numFund].displayHistory();
}

int Account::getId() const
{
	return ac_id;
}

string Account::getFirstName() const
{
	return first_name;
}

string Account::getLastName() const
{
	return last_name;
}

//to deposit into the account
bool Account::Deposit(int numFund, int depAmt)
{
	string toRecord = "D " + to_string(this->ac_id) + to_string(numFund) + " " + to_string(depAmt);

	if (canDeposit(numFund, depAmt))
	{
		this->ac_funds[numFund].addHistory(toRecord);
		return true;
	}
	else
	{
		this->ac_funds[numFund].addHistory(toRecord + "(Error/Failed)");
		return false;

	}
}

//to withdraw amount from the given fundIndex of  the account
bool Account::Withdraw(int numFund, int withDrawAmt)
{
	//string will get recorded in the vector of history whether it is success or not
	string toRecord = "W " + to_string(this->ac_id) + to_string(numFund) + " " + to_string(withDrawAmt);
	if (canWithdraw(numFund, withDrawAmt))
	{
		ac_funds[numFund].addHistory(toRecord);
		return true;
	}
	else
	{
		//error message to the console
		cout << "ERROR: Insufficient fund to withdraw $" << withDrawAmt << " (with combined fund (if applicable))" << endl;
		ac_funds[numFund].addHistory(toRecord + "(Error/Failed)");
		return false;
	}
}

//to transfer amount from this account to another
bool Account::Transfer(int numFund, int transferAmount, Account& toAc, int toFund)
{
	if ((numFund < 0 || numFund > 9) || (toFund < 0 || toFund > 9))
	{
		cout << "ERROR: Transfer cannot be made, invalid index to the fund of either this or destination account" << endl;
		return false;
	}
	if (transferAmount < 0)
	{
		cout << "ERROR: Transfer cannot be made, negative amount value" << endl;
		return false;
	}

	string toRecord = "T " + to_string(this->ac_id) + to_string(numFund) + " " + to_string(transferAmount) + " " +
		to_string(toAc.getId()) + to_string(toFund);

	if (canTransfer(numFund, transferAmount, toAc, toFund))
	{
		ac_funds[numFund].addHistory(toRecord);
		return true;
	}
	else
	{
		cout << "ERROR: Transfer canot be made. Insufficeint amount in the fund to make a transfer" << endl;
		ac_funds[numFund].addHistory(toRecord + "(Error/Failed)");
		return false;
	}

	//int tempAc = toAc.ac_id;
	//if (tree.Contains(tempAc))
	//{
	//	if (canTransfer(numFund, transferAmount, toAc, toFund))
	//	{
	//		ac_funds[numFund].addHistory(toRecord);
	//		return true;
	//	}
	//	else
	//	{
	//		cout << "ERROR: Transfer canot be made. Insufficeint amount in the fund to make a transfer" << endl;
	//		ac_funds[numFund].addHistory(toRecord + "(Error/Failed)");
	//		return false;
	//	}
	//}
	//else
	//{ 
	//	cout <<"ERROR: Transfer Refused. Account(" << tempAc << ") does not exist" << endl;
	//		//ac_funds[numFund].addHistory(toRecord + "(Error/Failed)");
	//	return false;
	//}

}

//helper method that checks for valid index to the funds that passed as parameter.
bool Account::canDeposit(int fundIndex, int amt)
{
	if (fundIndex >= 0 || fundIndex <= 9)
	{
		ac_funds[fundIndex].Add(amt);
		return true;
	}
	else if (amt < 0)
	{
		cout <<"invalid money amount" <<endl;
	}
	else
	{
		cout << "ERROR: " << fundIndex << " is not a vald index to the fund" << endl;
		return  false;
	}
}

//helper method that checks if withdraw can me made from the given fundIndex
//also checks for the linked accounts in case of insufficient funds
bool Account::canWithdraw(int fundIndex, int amt)
{
	if (fundIndex < 0 || fundIndex > 9)
	{
		cout << "ERROR: " << fundIndex << " is not a valid index to the fund" << endl;
		return false;
	}
	if (fundIndex == 0)
		return canWithDrawLinked(fundIndex, amt);
	else if(fundIndex == 1)
		return canWithDrawLinked(fundIndex, amt);
	else if(fundIndex == 2)
		return canWithDrawLinked(fundIndex, amt);
	else if (fundIndex == 3)
		return canWithDrawLinked(fundIndex, amt);
	else
	{
		if (ac_funds[fundIndex].getAmount() > amt)
		{
			if (ac_funds[fundIndex].deduct(amt))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
			return false;
	}
	//return true;
}

//helper method to check for the linked accouts and check if the withdraw can be made with 
//linking two different account funds 
bool Account::canWithDrawLinked(int fundIndex, int amount)
{
	//if withdraw can be made without the linked account, does that
	bool status = false;
	if (ac_funds[fundIndex].getAmount() >= amount)
	{
		status = ac_funds[fundIndex].deduct(amount);
		return status;
	}
	//tempfund for respective linked account of the parameter fundIndex
	int tempFunds;

	switch (fundIndex)
	{
	case 0:
		tempFunds = 1;
		break;
	case 1:
		tempFunds = 0;
		break;
	case 2: 
		tempFunds = 3;
		break;
	case 3: 
		tempFunds = 2;
		break;
	default:
		return status;
	}
	
	//amout tha this fund needs to borrow from another linked account
	int BorrowAmt = ac_funds[fundIndex].getAmount() - amount;
	if (BorrowAmt < 0)
	{
		if (abs(BorrowAmt) <= ac_funds[tempFunds].getAmount())
		{
			//deducts first form the linked fund and adds tp this fund and deducts the parameter amount after when sufficient
			ac_funds[tempFunds].deduct(abs(BorrowAmt));
			ac_funds[fundIndex].Add(abs(BorrowAmt));
			return ac_funds[fundIndex].deduct(amount);
		}
	}
	return true;
}

bool Account::canTransfer(int fundIndex, int transAmt, Account& toAc, int toFund)
{
	string toRecord = "T " + to_string(this->ac_id) + to_string(fundIndex) + " " + to_string(transAmt) + " " +
		to_string(toAc.getId()) + to_string(toFund);

	if (this->ac_funds[fundIndex].getAmount() < transAmt)
	{
		//cout << "PLEASEEEEEEEEEE work already " << endl;
		this->ac_funds[fundIndex].addHistory(toRecord + "(Error/Failed)");
		return false;
	}
	else
	{
		//cout << "SHITTTTTTTT this aint workkkking" << endl;
		ac_funds[fundIndex].deduct(transAmt);
		toAc.ac_funds[toFund].Add(transAmt);
		toAc.ac_funds[toFund].addHistory(toRecord);
		return true;
	}

}
