#include "account.h"
#include "binary_search_tree.h"
#include "transaction.h"
#include "bank.h"
#include<queue>
#include <fstream>
#include <sstream>
#include<iostream>
using namespace std;

Bank::Bank()
{
	//deafult constructor does nothing
}
Bank::Bank(const Bank& newBank)
{
	actions = newBank.actions;
	acTree = newBank.acTree;
}
//constructor that takes in input file and reads it
Bank::Bank(string fileName)
{
	ifstream in_file;
	in_file.open(fileName);

	if (in_file.is_open())
	{
		string action_phrase;
		while (!in_file.eof())
		{
			//if there is a blank line, breaks and continue to anther line
			getline(in_file, action_phrase);
			if (action_phrase.empty())
			{
				break;
			}
			char actionType;
			istringstream parseLine(action_phrase);
			parseLine >> actionType;

			//this creates transaction object for opening an account
			if (actionType == 'O')
			{
				string fname, lname;
				int acID;
				parseLine >> lname >> fname >> acID;

				Transaction openAC(actionType, fname, lname, acID);
				actions.push(openAC); //pushes an action to the actions queue

			}
			//to deposit or to withdraw
			else if (actionType == 'D' || actionType == 'W')
			{
				int temp; //to store combined acID and fundindex integer
				int amount, acID, fundIndex;
				parseLine >> temp >> amount;
				acID = temp / 10; //dividing temp by 1o to get the account id because fundindex is also attached in temp
				fundIndex = temp % 10; // remainder of temp after dividing by 10 is fundIndex
				
				Transaction depositOrWithdraw(actionType, acID, fundIndex, amount);
				actions.push(depositOrWithdraw);
			}
			//for transfer action
			else if (actionType == 'T')
			{
				int acID, fundIndex, amount, toAcID, toFundIndex;
				int fromTemp, toTemp; //one for from acount and another for toaccount
				parseLine >> fromTemp >> amount >> toTemp; //parsing data in the field
				acID = fromTemp / 10;
				fundIndex = fromTemp % 10;
				toAcID = toTemp / 10;
				toFundIndex = toTemp % 10;

				Transaction transferAmount(actionType, acID, fundIndex, amount, toAcID, toFundIndex);
				actions.push(transferAmount); //pushed to the action queue
			}
			else if (actionType == 'H')
			{
				int acID, amount;
				parseLine >> acID;

				Transaction forHistory(actionType, acID);
				actions.push(forHistory);
			}
			else
			{
				cout << "ERROR: The input is not Valid. Transaction REFUSED" << endl;
			}
		}
	}
	 
}

// this method executes the transactions from the queue 
// items from the queue gets poped off after the action is complete untill the queue is empty
void Bank::processActions()
{
	//Transaction action = actions.front();
	while (!actions.empty())
	{
		Transaction action = actions.front();
		//opens the account if doesnt exists already
		if (action.getActionType() == 'O')
		{
			if (acTree.Contains(action.getAccountID()))
			{
				cout << "ERROR: Account (" << action.getAccountID() << ") already exists. Transaction refused" << endl;
			}
			else
			{
				Account* start = new Account(action.getAccountID(), action.getLastName(), action.getFirstName());
				acTree.Insert(start);
			}
		}
		//for depositing
		else if (action.getActionType() == 'D')
		{
			Account* start;//= nullptr;
			int acID = action.getAccountID();
			int amt = action.getTransactionAmount();
			int fundIndex = action.getFundIndex();
			
			if (acTree.Retrieve(acID, start))
			{
				start->Deposit(fundIndex, amt);
			}
			else
			{
				cout << "ERROR: Transaction refused. Account doesnt exist" << endl;
			}

		}
		//for transfer
		else if (action.getActionType() == 'T')
		{
			Account* fromAccount;//= nullptr;
			Account* toAccount; //= nullptr;
			int fromAcID, fromFund, amt, toAcID, toFund;
			fromAcID = action.getAccountID();
			fromFund = action.getFundIndex();
			toAcID = action.getTransferAcID();
			toFund = action.getTransferFundIndex();
			amt = action.getTransactionAmount();

			//proceed only if toAccount exists
			if (acTree.Contains(toAcID))
			{
				if ((acTree.Retrieve(fromAcID, fromAccount)) && (acTree.Retrieve(toAcID, toAccount)))
				{
					//if (fromAccount->Withdraw(fromFund, amt))
					//{
					//	toAccount->Deposit(toFund, amt);
					//}
					if (fromAccount->Transfer(fromFund, amt, *toAccount, toFund))
					{
						//toAccount->Deposit(toFund, amt);
						//cout << " " << end;
					}
					else
					{
						cout << "ERROR: Transfer cannot be made.Not enough fund on Account(" <<
							fromAccount->getId() << ") to transfer to Account("
							<< toAccount->getId() << ") " << endl;
					}

				}
			}
			else
			{
				cout << "ERROR: Transfer cannot be made. Account (" << toAcID << ") does not exist" << endl;
			}
		}
		//to withdraw from the account
		else if (action.getActionType() == 'W')
		{
			Account* start; //= nullptr;
			int acID = action.getAccountID();
			int fundIndex = action.getFundIndex();
			int amt = action.getTransactionAmount();

			if (acTree.Retrieve(acID, start))
			{
				start->Withdraw(fundIndex, amt);
			}
			else
			{
				cout << "ERROR: Withdraw cannot be made. Account doesnt exist" << endl;
			}
		}

		//to display the history of the account or the fund
		else if (action.getActionType() == 'H')
		{
			if (action.getAccountID() <= 9999)
			{
				Account* start;//= nullptr;
				int acID = action.getAccountID();
				if (acTree.Retrieve(acID, start))
				{
					cout << endl;
					start->fullHistory();
					cout << endl;
				}
			}
			else
			{
				Account* start;//= nullptr;
				int acID = action.getAccountID() / 10; //dividing by ten so we can retrieve account id without fundId
				int fundIndex = action.getAccountID() % 10; //remainder of dividing account id will be the fund index
				if (acTree.Retrieve(acID, start))
				{
					start->fundHistory(fundIndex);
					cout << endl;
				}
			}
			
		}
		//throws out the first action that was in the queue
		actions.pop();

	}
}

void Bank::PrintActions()
{
	///cout << endl;
	cout << "Final Balances:" << endl;
	acTree.Display();
}

