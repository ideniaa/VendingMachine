// header
#ifndef MachineA_hpp
#define MachineA_hpp


#include <stdio.h>
#include "Machine.hpp"


class MachineA : public Machine
{
private:
     static int count;
public:
     MachineA(int q, int d, int n);    // constructor

     virtual bool makeChange(int amt) override;   // calc change to give back in coins


};

#endif /* MachineA_hpp */