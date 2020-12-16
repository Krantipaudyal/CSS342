// TheJollyBanker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "bank.h"

int main()
{
	//Bank JollyBank("input8.txt");
	Bank JollyBank("BankTransIn.txt");
	JollyBank.processActions();
	JollyBank.PrintActions();
	system("pause");
}

