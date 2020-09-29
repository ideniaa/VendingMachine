//
//  Machine.cpp
//  cs140_proj4
//
//  Created by Jun on 5/27/19.
//  Copyright © 2019 CSCI40. All rights reserved.
//

#include "Machine.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Keeps track of number of successful transactions
//int Machine::numOfTrans = 0;

// base constructor
Machine::Machine(int q, int d, int n)
     : initCoins(q, d, n), current(q, d, n), change(0, 0, 0)
{
}

// total cost of item
int Machine::getTotalCost() const
{
     return totalCost;     // in unit of cents
}

// returns description of each item
string Machine::getItemDescp() const
{
     return inVect[index].description;
}

// returns item code/selection number
string Machine::getItemCode() const
{
     return inVect[index].code;
}

// returns user's item selection and sets item index
string Machine::searchKey(string c)
{
     for (int i = 0; i < inVect.size(); i++)
     {
          if (c == inVect[i].code)
          {
               setItemIndex(i);
               return inVect[i].description;
          }
     }

}

// sets item index to display info on that item when called
void Machine::setItemIndex(int i)
{
     index = i;
}

// returns price of item
int Machine::getCost() const
{

     return inVect[index].price;
}


// returns payment entered by user
int Machine::getPayment() const
{
     return payment;
}

void Machine::resetPayment()
{
     payment = 0;
}

/*
 removeItem
 input: the index where the item located in the vector of Inventory
 output: deduct the quantity of the item
 */
void Machine::removeItem()
{
     inVect[index].quantity -= 1;
}


/*
addDollarsBill
input: one dollar bill (100 cents)
output: update the amount of dollars in machine in cents
*/
int Machine::addDollarBill()
{
     int d;   
     cin >> d;

     if (d == 0)    // if user enters 0 cancel item selection
     {
          return 0;
     }
     payment = d;
     dollars += 1;  // add 1 dollar to machine total;

     return addDollarBill();
}

// returns total dollar bills
int Machine::getDollars() const
{
     return dollars;
}

// returns cents converted to dollar format
double Machine::toDollar(int cents)
{
     double money;
     money = cents / 100.0;
     return money;
}


// add each purchase amount to the total cost
void Machine::addTotalCost()
{
     // total cost in dollars
     totalCost += inVect[index].price;
}

void Machine::addPayment()
{
}

// load inventory
void Machine::setInventory(Inventory& obj)
{
     this->inVect.push_back(obj);
}


// get the total amount of a Coins
int Machine::sumCoins(const Coins obj) const
{
     return 25 * obj.q + 10 * obj.d + 5 * obj.n;
}

// member function used to validate card. It is overriden by MachineC class
bool Machine::validCard(string cc)
{
     return 0;
}

/*
 inputPayment
 input : prompt user to input the amount of payment
         stop reading when input zero
 output: the total amount of coins,
         ignoring the input that is not divisable by 25, 10, 5
 */
int Machine::inputPayment()
{
     return 0;
}

 // returns total change amount to give back in cents
int Machine::calcChange()
{
     return payment - inVect[index].price;
}


// displays change to give back in quarters, dimes, and nickels
void Machine::printChange() const
{
     cout << "Your change of " << sumCoins(change) << " is given as:";
     cout << setw(20) << "\n\tquarter(s): " << change.q
          << setw(20) << "\n\tdime(s)   : " << change.d
          << setw(20) << "\n\tnickel(s) : " << change.n << endl;
}

// displays the product items available for each machine
void Machine::printItems() const
{
     cout << "Available items:\n";
     for (int i = 0; i < inVect.size(); i++)
     {
          cout << setw(5) << inVect[i].code
               << setw(5) << inVect[i].price
               << setw(20) << inVect[i].description << endl;
     }
}


void Machine::printReport(fstream& outdata) const
{
	float initBal = sumCoins(initCoins) / 100.0;
	float curBal = sumCoins(current) / 100.0;
	float cost = totalCost / 100.0;

	outdata << "Machine: " << model << endl;
	outdata << "Initial balance: $" << initBal << " ";

	outdata << "( " << dollars << " $, " << initCoins.q << " Q, "
		<< initCoins.d << " D, " << initCoins.n << " N)" << endl;

	outdata << "Number of valid transactions: " << numOfTrans << endl;
	outdata << "Total cost: $" << cost << endl;
	outdata << "Current balance: $" << curBal << " ";


	outdata << endl;
	// title
	outdata << "Machine Inventory:\n";
	// table
	outdata << "Code" << setw(10) << "Id" << setw(20) << "Description"
		<< setw(10) << "Initial" << setw(10) << "Current\n";

	// output items in inventor
	int size = inVect.size();
	for (int i = 0; i < size; i++)
	{
		outdata << setw(4) << right << inVect[i].code << setw(10)
			<< inVect[i].id << setw(20)
			<< inVect[i].description << setw(10)
			<< inVect[i].quantity << setw(10)
			<< inVect[i].initQnty << endl;
	}
}

