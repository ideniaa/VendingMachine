#include "MachineA.hpp"
#include <iostream>
#include <iomanip>

// initialize static variable
int MachineA::count = 0;

// Constructor
MachineA::MachineA(int q, int d, int n)
     : Machine(q, d, n)
{
     count++;
     model = "100A" + to_string(count);
}

// verified that there is enough change in machine to give back
bool MachineA::makeChange(int amt)
{
     // reset change to 0 for next machine calculation
     change.q = 0;
     change.d = 0;
     change.n = 0;

     // checks that we have enough change
     if (amt > sumCoins(current))
          return false;
     else
     {
          while (amt > 0)
          {
               if (amt > 25)
               {
                    amt -= 25;
                    change.q += 1;
               }
               else if (amt > 10)
               {
                    amt -= 10;
                    change.d += 1;
               }
               else
               {
                    amt -= 5;
                    change.n += 1;
               }
          }
          numOfTrans++;  // accumulates number of successful transactions for machineA
          // updates money in machine
          current.q -= change.q;
          current.d -= change.d;
          current.n -= change.n;
     }

     return true;
}


