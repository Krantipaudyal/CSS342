#include "binary_search_tree.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

BinarySearchTree::BinarySearchTree()
{
	//nothing needed here
	root = nullptr;
	size_ = 0;
}
//destructor to delete off the binsry search tree
BinarySearchTree::~BinarySearchTree()
{
	Delete();
}
//returns size of the bstree
int BinarySearchTree::get_size() const
{
	return size_;
}

//checkcs if the ac id is within the range and calls recurssive function to add
bool BinarySearchTree::Insert(Account* insAc)
{
	if (insAc->getId() < 1000 || insAc->getId() > 9999)
	{
		cout << "ERROR: Account ID is not Valid" << endl;
		return false;
	}
	return recurssiveInsert(this->root, insAc);
}

bool BinarySearchTree::Retrieve(const int& acID, Account*& p_account) const
{
	Node* curr = this->root;
	while (curr != nullptr)
	{
		if (curr->pAcct.getId() == acID)
		{
			p_account = &curr->pAcct;
			return true;
		}

		//go to right child if acID is less than parameter value
		if (curr->pAcct.getId() < acID)
		{
			curr = curr->right;
		}
		else //go to left side
		{
			curr = curr->left;
		}
	}
	return false;
}

//checks if the tree has nothing and returns booleeans
bool BinarySearchTree::IsEmpty()
{
	return (this->root == nullptr);
}

void BinarySearchTree::Delete()
{
	//calls recurssive delete method if the root is not null
	if (this->root != nullptr)
	{
		recursiveDelete(root);
	}
}
//this method uses a recurssive helper method to traverse through the tree
//and print out the whole tree in order
void BinarySearchTree::Display()
{
	Node* temp = root;
	if (temp != nullptr)
	{
		//traverses tree using a helper funciton 
		traverseTree(temp);
	}
	else
	{
		cout << "The Account Tree is Empty" << endl;
	}
}
//searches for the passed parameter account id and returns a bool accorgingly
 bool BinarySearchTree::Contains(const int& acID) const
{
	Node* curr = this->root;
	while (curr != nullptr)
	{
		if (curr->pAcct.getId() == acID)
		{
			return true;
		}
		if (curr->pAcct.getId() < acID)
		{
			curr = curr->right;
		}
		else
		{
			curr = curr->left;
		}
	}
	return false;
}


// this is a recurssive function to find the correct position of insert
bool BinarySearchTree::recurssiveInsert(Node* &whichNode, Account* insAC)
{
	//checks if the root is nullptr, if so creates a root for bstree
	if (whichNode == nullptr)
	{
		Node* temp = new Node;
		temp->pAcct = *insAC;
		whichNode = temp;
		whichNode->left = nullptr;
		whichNode->right = nullptr;
		return true;
	}
	//goes to the left if id of account is smaller 
	else if (insAC->getId() < whichNode->pAcct.getId())
	{
		 recurssiveInsert(whichNode->left, insAC);
	}
	//going to right side if id is greater
	else if (insAC->getId() > whichNode->pAcct.getId())
	{
		recurssiveInsert(whichNode->right, insAC);
	}
	//else
	//{
	//	return false;
	//}
}

//deletes each and every node of the tree
void BinarySearchTree::recursiveDelete(Node* deleteNode)
{
	if (deleteNode != nullptr)
	{
		//goes to right and left before deleting itself
		recursiveDelete(deleteNode->left);
		recursiveDelete(deleteNode->right);

		//deleteNode->pAcct = nullptr;
		delete(deleteNode);
		//deleteNode = nullptr;
	}
}

//traverses the tree and prints the tree in inorder traversal
void BinarySearchTree::traverseTree(Node* start)
{
	if (start != nullptr)
	{
		//goes to the left and prints everything 
		//and then goes to the right to print everything
		traverseTree(start->left);
		cout << start->pAcct << endl;
		traverseTree(start->right);
	}
}

