
#include "MachineC.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

// initialize static variable
int MachineC::count = 0;

// constructor
MachineC::MachineC(int q, int n, int d) :Machine(q, n, d)
{
     count++;
     model = "100C" + to_string(count);
}

string MachineC::getModel() const
{
     return model;
}

// checks card info is valid
bool MachineC::validCard(string Credit)
{
     const int size = 16;
     int a[size];
     int total1 = 0;
     int total2 = 0;
     int totalSum = 0;
     // Checks the amount of characters is equal to 16
     if (Credit.length() != size)
     {
          return false;
     }
     else
     {
          //Coverts string into an integer
          for (int i = 0; i < size; i++)
          {
               char Convert = Credit.at(i);
               int value = Convert - '0';
               a[i] = value;
          }
          // Add the total of the odd integers from left to right
          for (int i = size - 1; i >= 1; i -= 2)
          {
               total1 += a[i];
          }
          // Multiplies the integer by two and adds the total of the even integers together
          for (int i = size - 2; i >= 0; i -= 2)
          {
               a[i] *= 2;
               if (a[i] >= 10)
               {
                    a[i] = (a[i] - 10) + 1;

               }
               total2 += a[i];
          }
          // Adds the total of both the odd and even integers
          totalSum = total1 + total2;
          //Checks if the integer is divisible by 10
          if (totalSum % 10 == 0)
          {
              numOfTrans++;
               return true;
          }
          else
          {
               return false;
          }

     }
}

bool MachineC::makeChange(int amt)
{
     return true;
}

