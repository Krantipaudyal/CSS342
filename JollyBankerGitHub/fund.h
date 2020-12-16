#ifndef FUND_H
#define FUND_H
#include <vector>
#include<string>
#include<iostream>
#include<sstream>
using namespace std;
class Fund
{

public:
	Fund();
	Fund(string fundName);
	~Fund();


	bool Add(int amount);
	bool deduct(int amount);

	//getters and setters
	string getName() const; //get fund name
	int getAmount()const; //get amount total in the fund
	void setAmount(int amount); //sets amount total 
	void addHistory(string inpHis);
	void displayHistory();
	//to print out fund, name, amount
	friend ostream& operator << (ostream& outstream, const Fund& inFund)
	{
		outstream << inFund.fund_name << ": $" << inFund.balance_amount << endl;
		return outstream;
	}

private:
	int balance_amount;
	string fund_name;
	//collecting history idk how? may be an array or a vector
	//stores history of the fund
	vector<string> history;


};
#endif // FUND_H
