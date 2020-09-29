//
//  MachineB.hpp
//  cs140_proj4
//
//  Created by Jun on 5/27/19.
//  Copyright © 2019 CSCI40. All rights reserved.
//

#ifndef MachineB_hpp
#define MachineB_hpp

#include <stdio.h>
#include "Machine.hpp"

class MachineB : public Machine
{
private:
	static int count;
	int payOption;
public:
	// constructor
	MachineB(int q, int d, int n);

	// get the model of a Machine
	string getModel() const;

	// add the payment into a Machine
	virtual void addPayment() override;


	// add the payment into a Machine
	virtual int inputPayment() override;


	// calculate the change to give back and the current coins left
	// if true, increase the number of transaction
	virtual bool makeChange(int amt) override;
};

#endif /* MachineB_hpp */