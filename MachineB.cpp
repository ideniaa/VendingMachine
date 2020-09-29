//
//  MachineB.cpp
//  cs140_proj4
//
//  Created by Jun on 5/27/19.
//  Copyright © 2019 CSCI40. All rights reserved.
//

#include "MachineB.hpp"
#include <iostream>
#include <iomanip>

// initialize static variable
int MachineB::count = 0;


// Constructor
MachineB::MachineB(int q, int d, int n)
     : Machine(q, d, n)
{
     count++;
     model = "100B" + to_string(count);
}


// get the model of a Machine
string MachineB::getModel() const
{
     return model;
}


/*
 addPayment
 input : add the amount of payment into a Machine
 output: void;
         if option = 2, increase dollars by one;
 */
int MachineB::inputPayment()
{
     int value;
     cin >> value;

     if (value == 0)
     {
          return 0;
     }
     if (value > 0 && value <= 100 && value % 5 == 0)

     {
          payment += value;
     }

     return inputPayment();

}

/*
addPayment
input : add the amount of payment into a Machine
output: void;
if option = 1, add it to the current coins;
if option = 2, increase dollars by one;
*/
void MachineB::addPayment()
{
	if (payOption == 1)
	{
		dollars += 1;
	}
	else
	{
		current.q += payment / 25;
		current.d += payment % 25 / 10;
		current.n += payment % 25 % 10 / 5;
	}

}

/*
 makeChange
 input : the amount of change to give back
 output: return true if the change can be made;
         calculate the change of coins to give back;
         calculate the current coins in the machine;
         count the number of successful transaction;
 */

bool MachineB::makeChange(int amt)
{
     // if the total of the current coins is greater than the change
     if (sumCoins(current) > amt)
     {
          change.q = amt / 25;
          change.d = amt % 25 / 10;
          change.n = amt % 25 % 10 / 5;

          // if the current quarters are sufficent to make change
          if (current.q > change.q)
          {
               // update the current quarters
               current.q -= change.q;
          }
          // if the current quarters are not sufficient
          else
          {
               // use dimes and nickels for the extract change of quarters
               change.d += (change.q - current.q) * 25 / 10;
               change.n += (change.q - current.q) * 25 % 10 / 5;

               change.q = current.q;
               current.q = 0;
          }
     label:
          // if current dimes are sufficient to make change
          if (current.q > change.d)
          {
               current.d -= change.d;
          }
          else
          {
               // use nickels for the extract change of dimesS
               current.n += (change.d - current.d) * 10 / 5;

               change.d = current.d;
               current.d = 0;
          }

          if (current.n >= change.n)
          {
               current.n -= change.n;
          }
          else
          {
               change.q--;       // remove a quarter from change
               current.q++;      // add it back to current quarters

               // the rest amount of change to give back
               amt = amt - change.q * 25;

               change.d = amt / 10;
               change.n = amt % 10 / 5;

               // recalculate the amount of dimes for chagne
               goto label;
          }

          // increment the number of transaction
          numOfTrans++;

          return true;
     }
     return false;

}





