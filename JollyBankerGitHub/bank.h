#ifndef BANK_H
#define BANK_H
#include<string>
#include<queue>
#include "binary_search_tree.h"
#include "transaction.h"

using namespace std;

class Bank
{
public:
	Bank();
	Bank(const Bank& newBank);
	//constuctor that reads the input file and build the list of actions
	Bank(string fileName);

	//processes the actions from the queue one by one
	void processActions();
	//prints all the transactions and final balance in the account.
	void PrintActions();

private:
	//binary search tree that holds the accounts
	BinarySearchTree acTree;

	//queue to store the actions
	queue<Transaction> actions;
};
#endif // !BANK_H
