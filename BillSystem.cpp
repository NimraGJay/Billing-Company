/**********************************************************************
 * BillSystem.cpp - CSCI251 - Ass4 - BillSystem class definition
 * <NIMRA GAUHAR> <5949403> <12/24/2018>
 **********************************************************************/
#include <iostream>
#include <fstream>
#include "BillSystem.h"
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
using namespace std;


// ========== class BillSystem Public Function definitions ==========

// Destructor
BillSystem::~BillSystem()
{
	for(int i = 0 ; i <BRecs.size();i++){
		delete BRecs.at(i);
	}
}

// Reads data in "usage.txt" into BRecs vector
bool BillSystem::ReadFile(char *fname)
{
	ifstream fin(fname);//opening the file object
	if(fin.is_open()){
		string f;
		while(fin.peek()!=EOF){ //as long as file pointer isnt the EOF continue...
			fin>>f;
			while(f.empty()){
				fin>>f;
			}//while loop to ensure the f is entered in the string f variable.this also ignores any extra while lines we might have in a file
			BillRecord *BR; //decalring the Bill record pointer it will later be initialised to the desired object
			if(f=="Elect"){
				BR= new ELectBillRecord;//allocates memory for the object
		 		BR->ReadCustDetails(fin);//reads deets
				BR->ReadUsageInfo(fin);
				BR->setBType(0);//seys yhe BType to 0:which is eElect
		 		BRecs.push_back(BR);//adds to the BRecs Vector
			}else if(f=="Gas"){
				BR= new GasBillRecord;
		 		BR->ReadCustDetails(fin);
				BR->ReadUsageInfo(fin);
				BR->setBType(1);
		 		BRecs.push_back(BR);
			}else if(f=="Phone"){
				BR= new PhoneBillRecord;
		 		BR->ReadCustDetails(fin);
				BR->ReadUsageInfo(fin);
				BR->setBType(2);
		 		BRecs.push_back(BR);				
			}else{
				cout<"\nERROR\n";
			}

		}

		return true;
	}else{
		cout<<"File Not Found";
		return false;
	}
		
}

// Returns the number of records in BRecs
int BillSystem::GetNumRecs()
{
	return BRecs.size(); 
}

 // Displays ith record on screen
void BillSystem::DisplayRec(int i)
{
	BRecs[i]->DisplayCustDetails();
	BRecs[i]->DisplayUsageInfo();
	cout<<endl;
}
//it adds discounts to users who deserve them
void BillSystem::CalDiscounts(){
	
	//multimap myMap stores name and address f=of all customers with Alinta and Dodo as their supplier
	multimap<string,string> myMap;
	multimap<string,string>::iterator it;
	string a,b,addr;
	
	for(int i = 0 ; i < BRecs.size();i++){
		a=BRecs[i]->getSupplier();
		if(a=="Dodo"||a=="Alinta"){
			b=BRecs[i]->getName();
			addr=BRecs[i]->getAddress();
			myMap.insert(make_pair(b,addr));

		}
	}
	
	//multiMap myMap2 stores only the Customers with all the three services so only custs with discount
	multimap<string,string> myMap2;	
	int c=1;//count to keep track of the no od cust services
	int dodo=0,atlinto=0;//count to keep track of dodo cust
	for(it=myMap.begin();it!=myMap.end();it++){

		auto fCur=it->first;
		auto sCur=it->second; //values of current iterator
		it++;
		if(it==myMap.end()){
			break;
		}
		auto fNext=it->first;
		auto sNext=it->second; //values of next iterator
		it--;

		if(fCur==fNext && sCur==sNext){ //current iterator compared with nect iterator. if theyre identical service count(c)++
			c++;
			if(c==3){ //means all the three services taken by this particulat Customer
				myMap2.insert(*it);//insert that particulat Customer in myMap2
				for(int i = 0 ; i <BRecs.size();i++){ //iterate thru the whole BRecs to change their Discount
					if(it->first==BRecs[i]->getName()&&it->second==BRecs[i]->getAddress()){
						if(BRecs[i]->getSupplier()=="Dodo"){
							BRecs[i]->SetDiscount(0.85);
							dodo++;
							
						}else if(BRecs[i]->getSupplier()=="Alinta"){
							BRecs[i]->SetDiscount(0.80);
							atlinto++;
						}
					}
				}
			}
		}
		else{	
			c=1;
		}
	}
	dodo/=3; //divide by 3 in in BRecs the Customers are init thrice for all the three services
	atlinto/=3;
	cout<<"\nNo of Discounts for Dodo: "<<dodo<<"\nNo of Discounts for Alinta: "<<atlinto<<endl<<endl;
	
}
void BillSystem::CalBills(){
	for(int i = 0 ; i <BRecs.size();i++){
		BRecs[i]->UpdateBalance(); //calls UpdateBalance to each Bill Record in BRecs
	}
}
void BillSystem::PrintReport(){
		cout<<left<<setw(3)<<"#"<<setw(15)<<"Service"<<setw(20)<<"Customer"<<setw(30)<<"Address"<<setw(4)<<"Bill Amount"<<endl;
		cout<<"-------------------------------------------------------------------------------\n";
	for(int i = 0 ; i <5;i++){//prints the required values
		cout<<left<<setw(3)<<i+1<<setw(15)<<BRecs[i]->getBType()<<setw(20)<<BRecs[i]->getName()<<setw(30)<<BRecs[i]->getAddress()<<setw(4)<<BRecs[i]->getBillAmount()<<endl;
	}
	cout<<endl<<endl;
	//printing the Customers and Addresses of Customers with Discount
	cout<<left<<setw(20)<<"Customer"<<setw(30)<<"Addresss"<<endl;
	cout<<"------------------------------------------\n";
	for(int i = 0 ; i <500;i++){
		if(BRecs[i]->getDiscount()!=1 && BRecs[i]->getBType()=="Gas")
		cout<<left<<setw(20)<<BRecs[i]->getName()<<setw(30)<<BRecs[i]->getAddress()<<endl;
	}
}
// ========== class BillSystem Private Function definitions ==========

