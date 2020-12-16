#ifndef TRANSACTION_H
#define TRANSACTION_H
#include<string>
using namespace std;

class Transaction
{
	friend ostream& operator<<(ostream& out, const Transaction& action);
public:
	Transaction();
	Transaction(char actionType, string fName, string lName, int acID); //to open a new account
	Transaction(char actionType, int acID, int fundIndex, int amount); // to deposit or withdraw amount to the account number in the given fund
	//to transfer x amount from one fundindex of this account to another account
	Transaction(char actionType, int fromAcID, int fromFundIndex, int amount, int toAcID, int toFundIndex);
	Transaction(char actionType, int acID); //for the history

	string getFirstName()const;
	string getLastName()const;
	int getAccountID()const;
	int getFundIndex() const;
	int getTransactionAmount() const;
	int getTransferAcID() const;
	int getTransferFundIndex() const;
	char getActionType() const;

	void setActionType(char actionType);
	void setFirstName(string fname);
	void setLastName(string lname);
	void setAccountID(int acID);
	void setFundIndex(int fundIndex);
	void setTransactionAmount(int value);
	void setTransferAcID(int transferAcID);
	void setTransferFundIndex(int transferFundIndex);


private:
	char action_type;
	string last_name;
	string first_name;
	int ac_id;
	int fund_index;
	int amount_;
	int to_ac_id;
	int to_fund_index;

};
#endif // !TRANSACTION_H
