//
//  main.cpp
//  cs140_proj4
//
//  Created by Jun on 5/18/19.
//  Copyright © 2019 CSCI40. All rights reserved.
//
#include "Machine.hpp"
#include "MachineB.hpp"
#include "MachineA.hpp"
#include "MachineC.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


typedef vector<shared_ptr<Machine>> vect_sptrMachine;

// function prototype
void readProducts(fstream&, vectInv&);
void readMachines(fstream&, vect_sptrMachine&, vectInv&);



int main(int argc, const char * argv[])
{
     // declare variables
     vectInv vectProd;
     vect_sptrMachine machines;
     string startCode;           // spring19
     string machineModel;
     string itemdescp;
     string itemCode;
     string card;        // holds card number
     int itemIndex;
     int mIndex;                 // index of models in a vector to machines
     int payment;
     int payOption;
     int itemCost;
     int back;                   // amount of change to give back
     bool valid = false;

     // ask user to enter the start code
     cout << "Please enter a startup code --> ";
     cin >> startCode;

     // check user code, if invalid have user re-enter
     while (startCode != "spring19")
     {
          cout << "Startup code is incorrect. Please try again.\n";
          cout << "Please enter a startup code --> ";
          cin >> startCode;
     }

     // start to initialize machines
     cout << "Initialize machine. Please wait...\n";

     fstream prodFile("products.txt", ios::in);
     fstream machFile("machines.txt", ios::in);
     readProducts(prodFile, vectProd);
     readMachines(machFile, machines, vectProd);

     cout << "Machine ready.\n"
     << "Available machines: 100A1, 100A2, 100B1, 100C1, 100C2\n";

     // ask user to select machine
     cout << "Select a machine --> ";
     cin >> machineModel;

     // while loop for multiple machine selections
     while (machineModel != "spring19")
     {
          // if user select 100A machine
          if (machineModel == "100A1" || machineModel == "100A2")
          {
               // get the index of the selected model
               if (machineModel == "100A1") { mIndex = 0; }
               else { mIndex = 1; }

               cout << "This machine accepts one-dollar bill only.\n";

          }// if user selects 100B machine
          else if (machineModel == "100B1")
          {
               mIndex = 2;

               cout << "This machine accepts coins or one-dollar.\n";
          }
          else
          {    // if user selects 100C machine
               if (machineModel == "100C1") { mIndex = 3; }
               else { mIndex = 4; }

               cout << "This machine accepts credit card only.\n";
          }

          // list machine inventory
          machines[mIndex]->printItems();

          // prompt user to select an item code
          cout << "Select an item --> ";
          cin >> itemCode;

           // print the selected item info
          cout << "You selected " << machines[mIndex]->searchKey(itemCode);
          cout << "\nThe cost of this item is " << machines[mIndex]->getCost() << " cents.\n";

         // Pay in coins(option2) or dollar bill(option 1) (Machine B)
         if (machineModel == "100B1")
         {
			 // prompt user to select an payment option
			 cout << "Select an option(1 -> one-dollar bill; 2 -> coins) --> ";
			 cin >> payOption;

			 if (payOption == 2)
			 {
				 cout << "Please insert you coins --> ";
			 }
			 else {

				 // prompt user to input payment
				 cout << "Please insert your money --> ";
			 }
			 machines[mIndex]->inputPayment();
			
         }
         // Pay in dollar bill only (Machine A)
         if (machineModel == "100A1" || machineModel == "100A2")
         {
		// prompt user to input payment
              cout << "Insert your money --> ";
              machines[mIndex]->addDollarBill();
             
         }

		    // Cancel if user enters 0 or continue with transaction if user enters money
		 if (machines[mIndex]->getPayment() == 0)
		 {
			 cout << "You chose to cancel your selection\n";
		 }
		 else
		 {
			 cout << "You entered an amount of " << machines[mIndex]->getPayment() << " cents.\n";
			 cout << "Processing your purchase...\n";

			 // calculate the change to give back
			 back = machines[mIndex]->calcChange();

			 // if the change is able to make display change else display no change
			 if (machines[mIndex]->makeChange(back))         // number of transaction updates here
			 {
				 machines[mIndex]->removeItem();    // removed item from inventory
				 machines[mIndex]->addTotalCost();  // adds cost to machine
				 machines[mIndex]->addPayment();					//	machines[mIndex]->addPayment();
				 machines[mIndex]->printChange();   // display change back to user

				 cout << "Thank you! Please take your item.\n";
			 }
			 else
			 {
				 cout << "Insufficient changes!\n";
				 cout << "Your transaction cannot be processed.\n";
				 cout << "Please take your dollar bill back.\n";
			 }

		 }
         machines[mIndex]->resetPayment();   // reset payment variable back to 0 ready for next purchase

          // Pay credit card (Machine C)
          if (machineModel == "100C1" || machineModel == "100C2")
          {
               // variable keeps count of invalid attempts
               int count = 1;

               // prompt user for credit card info
               cout << "Enter your credit card number -->";
               cin >> card;

               // loop for incorrect card number
               while (!(machines[mIndex]->validCard(card)))
               {
                    cout << "Invalid credit card number was entered.\n";
                    cout << "Enter your credit card number -->";
                    cin >> card;
                    ++count;

                    // 2 invalid attempts will cancel item selection
                    if (count == 2)
                    {
                         cout << "Too many invalid attempts. Your selection is cancelled.\n";
                         goto Label3;
                    }
               }
               // update inventory if card process
               machines[mIndex]->removeItem();    // removed item from inventory
               machines[mIndex]->addTotalCost();  // adds cost to machine

               cout << fixed << showpoint << setprecision(2);
               cout << "Your card was successfully charged for $" << machines[mIndex]->toDollar(machines[mIndex]->getCost());
               cout << "\nThank you! Please take your item.\n";
          }

     Label3:     // go to next machine selection
          cout << "\nSelect a machine --> ";
          cin >> machineModel;
     }

          // user entered code to shut down machines
          cout << "Report is generating...\n";
          cout << "System is shutting down.\n\n";
      

          // open the output file
          fstream outdata("machineOutput.txt", ios::out);

          // print out the report
          for (int i = 0; i < machines.size(); i++)
          {
               machines[i]->printReport(outdata);
              // machines[i]->printInventory();
               outdata << endl << endl;
          }

          outdata.close();
		  system("pause");
     return 0;
}


// load master product inventory for machines
void readProducts(fstream& indata, vectInv& vectProd)
{
     Inventory temp;

     if (!indata)
     {
          cout << "Errors in opening the file.\n";     // displays error if cannot open txt file
          exit(1);
     }

     while (!indata.eof())
     {
          indata >> temp.id >> temp.quantity >> temp.price;

          getline(indata, temp.description);

          vectProd.push_back(temp);
     }

     indata.close();
}

// load all machines into vector for use
void readMachines(fstream& infile, vect_sptrMachine& machines, vectInv& products)
{
     shared_ptr<Machine> m;
     Coins coin;
     string model;
     string code;
     string descp;
     int prodQuant = 0;
     int price = 0;
     int Id;
     int machineQaunt = 0;
     int numOfModels;
     int numOfItems;
     int pIndex;

     if (!infile)
     {
          cout << "Errors in opening the file.\n";     // displays error if cannot open txt file
          exit(1);
     }

     // read from machines.txt file
     while ((infile.peek()) != EOF)
     {
          infile >> model >> numOfModels;

          // loop to load each machine model
          for (int i = 0; i < numOfModels; i++)
          {
               infile >> coin.q >> coin.d >> coin.n >> numOfItems;

               // initialize the Machine
               if (model == "100A")
               {
                    m = make_shared<MachineA>
                         (coin.q, coin.d, coin.n);

               }
               if (model == "100B")
               {
                    m = make_shared<MachineB>
                         (coin.q, coin.d, coin.n);

               }
               if (model == "100C")
               {
                      m = make_shared<MachineC>
                      (coin.q, coin.d, coin.n);
               }
			   if (model == "100D")
			   {
				   infile.seekp(0, ios::end);
				   infile.seekg(0, ios::end);
			   }

               //loop to load the inventory items for eache model
               for (int j = 0; j < numOfItems; j++)
               {
                    // read product's code, id, quantity in a Machine
                    infile >> code >> Id >> machineQaunt;

                    // loop over the vector of products
                    for (pIndex = 0; pIndex < products.size(); pIndex++)
                    {
                         if (products[pIndex].id == Id)
                         {
                              descp = products[pIndex].description;   // get description
                              prodQuant = products[pIndex].quantity;  // get quantity in the inventory
                              price = products[pIndex].price;         // get price
                              break;      // break out of the product loop
                         }
                    }

                    // if not enought items in the inventory
                    if (prodQuant <= machineQaunt)
                    {
                         // take all of items from the stock
                         // and set the stock for that item to zero
                         machineQaunt = prodQuant;
                         products[pIndex].quantity = 0;
                    }
                    else
                    {
                         // updat the stock
                         products[pIndex].quantity -= machineQaunt;
                    }


                    // fill an item in the inventory
                    Inventory temp(Id, machineQaunt, price, descp, code);
                    m->setInventory(temp);
               }

               // add the Machine to its list of vector
               if (model == "100A")
               {
                    // dd a model 100A to vector of MachineA
                   machines.push_back(static_pointer_cast<MachineA>(m));
               }
               if (model == "100B")
               {
                    // add a model 100B to vector of MachineB
                    machines.push_back(static_pointer_cast<MachineB>(m));
               }
               if (model == "100C")
               {
                      // add a model 100B to vector of MachineB
                     machines.push_back(static_pointer_cast<MachineC>(m));

               }

          }

     }
     infile.close();     

}

