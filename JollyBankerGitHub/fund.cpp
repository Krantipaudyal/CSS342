#include<iostream>
#include"fund.h"
#include<string>


//deafult constructor
Fund::Fund()
{
	balance_amount = 0;
}

//takes in a string parameter as fund name 
Fund::Fund(string fundName)
{
	fund_name = fundName;
	balance_amount = 0;
}

Fund::~Fund()
{
	//destructor
}

//adds to the fund and update histpry if succeded
bool Fund::Add(int amount)
{
	if (amount > 0)
	{
		this->balance_amount += amount;
		//this->addHistory("SUCCESS: Amount added to the fund is: $" + amount);
		return true;
	}
	else
	{
		cout << "ERROR: Could not add Negative Value" << endl;
		//this->addHistory("ERROR: Could not add Negative Value");
		return false;
	}
}

//subtracts the amount from the total amount
bool Fund::deduct(int amount)
{
	if(amount > 0)
	{
		this->balance_amount -= amount;
		//this->addHistory("SUCCESS: Deducted amounf from the fund is: $" + amount);

		return true;
	}
	else
	{
		cout << "ERROR: Could not deduct negative amount" << endl;
		//this->addHistory("ERROR: Could not deduct negative amount");
		return false;

	}
}

string Fund::getName() const
{
	return this->fund_name;
}

//returns the total balance in the fund
int Fund::getAmount() const
{
	return this->balance_amount;
}

//sets  the amount to the fund
void Fund::setAmount(int amount)
{
	if(amount > 0)
	{
		this->balance_amount = amount;
		//this->addHistory("SUCCESS: Amount set to the fund is: $" + amount);

	}
	else
	{
		cout << "ERROR: Cannot set negative amount as total fund amount" << endl;
		//this->addHistory("ERROR: Cannot set negative amount as total fund amount");
	}
}

//Adds the parameter string to the history
void Fund::addHistory(string inpHis)
{
	this->history.push_back(inpHis);
}

//print outs the history of funds
void Fund::displayHistory()
{
	if (history.size() == 0)
	{
		//cout << "There were no transactions on this fund. No History Found" << endl;
	}
	else
	{
		for (int i = 0; i < history.size(); i++)
		{
			cout << this->history[i] << endl;
		}
		
	}
}
