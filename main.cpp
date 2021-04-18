/**********************************************************************
 * main.cpp - CSCI251 - Ass4- main() tester for class BillSystem
 * <NIMRA GAUHAR> <5949403> <12/24/2018>
 **********************************************************************/
#include <iostream>
#include "BillSystem.h"
#include <iomanip>
using namespace std;
 
char Menu();

int main(){

	BillSystem BS;

	cout << "Begin tests for BillSystem\n\n";

	if(!BS.ReadFile("usage.txt")){
		cout << "File not found!\n\n";
		exit(1);
	}
	int n = BS.GetNumRecs();

	cout << "Num records read: " << n << endl << endl;
	cout<<left<<setw(3)<<"#"<<setw(10)<<"Type"<<setw(15)<<"Supplier"<<setw(20)<<"Name"<<setw(35)<<"Address"<<setw(15)<<"AccBal"<<setw(15)<<"Days"<<endl;
	cout<<"------------------------------------------------------------------------------------------------------\n";
	for(int i=0; i<n && i<5; i++){
		cout<<setw(3)<<i+1;
		BS.DisplayRec(i);
	}
	
	BS.CalDiscounts(); // uncoment when step 3 complete
	
	BS.CalBills();     // uncoment when step 4 complete
	BS.PrintReport();  // uncoment when step 4 complete

	cout << endl << "End tests for BillSystem\n";

	return 0;
}

