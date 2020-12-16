
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "account.h"
class BinarySearchTree
{
public:

	//constructors, copy constructors and destructors
	BinarySearchTree();
	//BinarySearchTree(const BinarySearchTree& bst); //NO NEED OF COPY CONSTRUCTORS
	~BinarySearchTree();
	 
	//getter method for size
	int get_size() const;

	//actions in the bstres
	bool Insert(Account *insAc);
	bool Retrieve(const int& acID, Account*& p_account) const;  // peeks if the acID exits, returns the account to the rference parameter
	bool IsEmpty(); //checks if the tree is empty 
	void Delete(); //delete the tree
	void Display(); //displays the tree contains
	bool Contains(const int& acID) const; //check if the account exists already
	//friend bool isAvailable(BinarySearchTree& bst);



private:
	//node struct to hold reference to the left and right child and account object 
	struct Node
	{
		Account pAcct;
		Node* left;
		Node* right;

	};
	Node* root;
	int size_; //end up not using this integer lolll

	bool recurssiveInsert(Node* &whichNode, Account* insAC); //recursive insert
	void recursiveDelete(Node* deleteNode); //recursive delete
	void traverseTree(Node* start); //traverses the tree for display
};
#endif // !BINARY_SEARCH_TREE_H
