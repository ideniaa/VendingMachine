#pragma once
#ifndef MachineC_h
#define MachineC_h
#include <stdio.h>
#include "Machine.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MachineC : public Machine
{

private:
     static int count;
public:
     // Constructor for Machine C
     MachineC(int q, int n, int d);

     // Gets the model of the machine
     string getModel() const;

     // Checks if credit/debit card is valid
     virtual bool validCard(string) override;

     // Make change is false
     virtual bool makeChange(int amt) override;
};

#endif /* MachineC_h */

