#include<queue>
#include<iostream>
#include<vector>
#include<string>
#include "transaction.h"


ostream& operator<<(ostream& out, const Transaction& action)
{
	return out;
}

Transaction::Transaction()
{
	//deafult constructor
}

//overloaded constructor for opening account 
Transaction::Transaction(char actionType, string fName, string lName, int acID)
{
	action_type = actionType;
	first_name = fName;
	last_name = lName;
	ac_id = acID;
}

//constructor for depositing money or withdrawing
Transaction::Transaction(char actionType, int acID, int fundIndex, int amount)
{
	action_type = actionType;
	ac_id = acID;
	fund_index = fundIndex;
	amount_ = amount;
}

//to transfer money from one fund of that ac to another fund of another account
Transaction::Transaction(char actionType, int fromAcID, int fromFundIndex, int amount, int toAcID, int toFundIndex)
{
	action_type = actionType;
	ac_id = fromAcID;
	fund_index = fromFundIndex;
	amount_ = amount;
	to_ac_id = toAcID;
	to_fund_index = toFundIndex;
}

//this is for the history of all the transactions
Transaction::Transaction(char actionType, int acID)
{
	action_type = actionType;
	ac_id = acID;
}

string Transaction::getFirstName() const
{
	return this->first_name;
}

string Transaction::getLastName() const
{
	return this->last_name;
}

int Transaction::getAccountID() const
{
	return this->ac_id;
}

int Transaction::getFundIndex() const
{
	return this->fund_index;
}

int Transaction::getTransactionAmount() const
{
	return this->amount_;
}

int Transaction::getTransferAcID() const
{
	return this->to_ac_id;
}

int Transaction::getTransferFundIndex() const
{
	return to_fund_index;
}

char Transaction::getActionType() const
{
	return this->action_type;
}


void Transaction::setActionType(char actionType)
{
	action_type = actionType;
}

void Transaction::setFirstName(string fname)
{
	first_name = fname;
}

void Transaction::setLastName(string lname)
{
	last_name = lname;
}

void Transaction::setAccountID(int acID)
{
	ac_id = acID;
}

void Transaction::setFundIndex(int fundIndex)
{
	fund_index = fundIndex;
}

void Transaction::setTransactionAmount(int value)
{
	amount_ = value;
}

void Transaction::setTransferAcID(int transferAcID)
{
	to_ac_id = transferAcID;
}

void Transaction::setTransferFundIndex(int transferFundIndex)
{
	to_fund_index = transferFundIndex;
}
