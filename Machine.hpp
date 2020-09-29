//
//  Machine.hpp
//  cs140_proj4
//
//  Created by Jun on 5/27/19.
//  Copyright © 2019 CSCI40. All rights reserved.
//

#ifndef Machine_hpp
#define Machine_hpp

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Inventory
{
     int id;
     int quantity;
     int initQnty;       // initial quantity
     int price;
     string description;
     string code;

     Inventory(int Id = 0, int q = 0, int p = 0, string ds = "", string c = "")
          : id(Id), quantity(q), initQnty(q), price(p), description(ds), code(c) {}

};


struct Coins
{
     int q, d, n;

     Coins(int q = 0, int d = 0, int n = 0)
          : q(q), d(d), n(n) {}

};

// refined a vector to inventory
typedef vector<Inventory> vectInv;


class Machine
{
protected:
     Coins current;                 // current money in vending machine
     Coins change;                  // change to give back
     Coins initCoins;               // initial coins
     vectInv inVect;                // a vector of inventory for a Machine
     int dollars = 0;
     int payment = 0;
     int totalCost = 0;
     int numOfTrans = 0;
     string model = "";
     int index;

public:
     // constructor
     Machine(int q, int d, int n);

     // get the amount of total purchase
     int getTotalCost() const;

     // get all of one dollar bills
     int getDollars() const;

         // get item description from inventory vector
     string getItemDescp() const;

     // get Code for an item
     string getItemCode() const;

     // get cost of an item for its code
     int getCost() const;

     // get the amount of payment 
     int getPayment() const;

     // remove one item from a Inventory
     void removeItem();

     // add one-dollar bill input by customer
     int addDollarBill();

     // converts cents to dollar format;
     double toDollar(int cents);

         // add all of purchase into totalCost
     void addTotalCost();

     // initialize an inventory
     void setInventory(Inventory& obj);

     // calculate the total coins for a Coin object
     int sumCoins(const Coins obj) const;

     // print the change to give back
     void printChange() const;

     void printItems() const;

     // prints final report of all machines
     void printReport(fstream& outdata) const;

	 // get the amount of payment in coins from user
	 virtual int inputPayment();

	 // gets payment for machineB
	 // includes special case solution
	 virtual void addPayment();

     // Pure virtual function
     // return true if the transaction is valid, false otherwise
     virtual bool makeChange(int amt) = 0;

     // checks credit card numbers are valid
     virtual bool validCard(string cc);

     // searches for user item selection
     string searchKey(string c);

     // calculates total cents to give back
     int calcChange();

     // reset variable payment to 0 for next purchase
     void resetPayment();

     // sets chosen item index to display all of its info
     void setItemIndex(int i);
};


#endif /* Machine_hpp */

