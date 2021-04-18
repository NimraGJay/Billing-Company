/**********************************************************************
 * BillSystem.h - CSCI251 - Ass4- BillSystem class declaration
 * <NIMRA GAUHAR> <5949403> <12/24/2018>
 **********************************************************************/
#ifndef BILLSYS_H
#define BILLSYS_H

#include <iostream>
#include <vector>
#include "BillRecord.h"
using namespace std;


class BillSystem {
  public:
    ~BillSystem();
     bool ReadFile(char *fname);
     int GetNumRecs();
     void DisplayRec(int i); // prints ith record on screen
     void CalDiscounts();
     void CalBills();
     void PrintReport();
	
  private:
     vector<BillRecord*> BRecs; // vector of pointers to class BillRecord
};
#endif

