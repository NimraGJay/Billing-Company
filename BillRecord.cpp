/**********************************************************************
 * BillRecord.cpp - CSCI251 - Ass4 - BillRecord class definition
 * <NIMRA GAUHAR> <5949403> <12/24/2018>
 **********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "BillRecord.h"
using namespace std;

// ========== class BillRecord function definitions ==========

// Default constructor
BillRecord::BillRecord(){
BillAmount=-1;
Discount=1;
}

//BType Setter
void BillRecord::setBType(int n){
	switch(n){
		case 0:
			BType=eElect;
			break;
		case 1:
			BType=eGas;
			break;
		case 2:
			BType=ePhone;
			break;
	}
}
// Reads customer details part of record from file
bool BillRecord::ReadCustDetails(ifstream &fin)
{
	bool b=false;
//	string s;
//	fin>>s;
//	while(s.empty()){
//		fin>>s;
//	}
//	if(s=="Phone")
//		BType=ePhone;
//	else if(s=="Elect")
//		BType=eElect;
//	else	
//		BType=eGas;
	//cout<<s<<endl;
	getline(fin,Supplier);
	while(Supplier.empty()){
		getline(fin,Supplier);
	}
	//	cout<<"Supplier : "<<Supplier<<endl;
	getline(fin,Name);
	while(Name.empty()){
		getline(fin,Name);
	}
	//	cout<<"Customer : "<<Name<<endl;
	
	getline(fin,Address);
	while(Address.empty()){
		getline(fin,Address);
	}
	//	cout<<"Address : "<<Address<<endl;
	fin>>AccountBalance;
	//	cout<<"Account Balance : "<<AccountBalance<<endl;
	fin>>DaysSinceLastReading;
	//	cout<<"DaysSinceLastReading : "<<DaysSinceLastReading<<endl;
//put code here for reading the customer details part of file record only into the private data members
	b=true;
	return b;
}

// Displays customer details part of record on screen
void BillRecord::DisplayCustDetails()
{
	string type;
	switch(BType){
		case 0:
			type="Elect ";
			break;
		case 1:
			type="Gas ";
			break;
		case 2:
			type="Phone ";
			break;
		
	}
	cout<<setw(10)<<type<<setw(15)<<Supplier<<setw(20)<<Name<<setw(35)<<Address<<setw(15)<<AccountBalance<<setw(15)<<DaysSinceLastReading;
	//display customer details (only) from private data members
}

// Virtual fn for reading usage info part of record from file in derived classes
bool BillRecord::ReadUsageInfo(ifstream &fin)
{
	bool b = false;
	double d;
	switch(BType){
		case 2:
			//cout<<"PHONE ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" "<<endl;
				b= true;
			break;
		case 0:
			//cout<<"ELECT ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" "<<endl;
			//fin.ignore(256,'\n');
				b= true;
			break;
		case 1:
			//cout<<"GAS ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" ";
			fin>>d;//cout<<d<<" "<<endl;
			//fin.ignore(256,'\n');
				b= true;
			break;
	}
	//the code here should jusy test BillType and read (eat) the usage info from file and discard it
	//later we will override this fn to read usage info into the approbriate derived classes private data members

	return b;
}


// virtual fn for displays usage info part of record in derived classes
void BillRecord::DisplayUsageInfo()
{
	// does nothing - later we will override this fn to display the appropriate billing info in the derived classes
}
void BillRecord::SetDiscount(float d){
	Discount=d;	
};
string BillRecord::getSupplier(){
	return Supplier;
}
string BillRecord::getName(){
	return Name;
}
string BillRecord::getAddress(){
	return Address;
}
double BillRecord::getAccntBalance(){
	return AccountBalance;
}
void BillRecord::setAccountBalance(double d){
	AccountBalance=d;
}
string BillRecord::getBType(){
	string s="";
	switch(BType){
		case eElect:
			s="Elect";
			break;
		case eGas:
			s="Gas";
			break;
		case ePhone:
			s="Phone";
			break;
		
	}
	return s;
}
double BillRecord::getBillAmount(){
	return BillAmount;
}
float BillRecord::getDiscount(){
	return Discount;
}
// ========== Derived Class function definitions ==========


// write the function definitions of the derived classes here
bool ELectBillRecord::ReadUsageInfo(ifstream &fin){
	//cout<<"Elect"<<endl;
	fin>>prevReading>>curReading>>rt1>>rt1Threshold>>rt2>>supplyCharge;	
}

void ELectBillRecord::DisplayUsageInfo(){
	cout<<"\n(Readings:"<<prevReading<<","<<curReading<<"\t\t"<<"R1:";
	cout<<rt1<<" R1Th:"<<rt1Threshold<<" R2:"<<rt2<<" SC:"<<supplyCharge<<")"<<endl;
}

void ELectBillRecord::UpdateBalance(){	//done by formulae
	double C,P;
	C=curReading-prevReading;
	P=supplyCharge*DaysSinceLastReading;
	if(C<=rt1Threshold ){
		BillAmount=(C*rt1+P)*Discount-getAccntBalance();
	}else{
		BillAmount=(rt1Threshold*rt1+(C-rt1Threshold)*rt2+P)*Discount-getAccntBalance();
	}
	setAccountBalance(0);
}
bool GasBillRecord::ReadUsageInfo(ifstream &fin){
	//cout<<"Gas"<<endl;
	fin>>prevReading>>curReading>>heatingValue>>rt>>supplyCharge;
}
void GasBillRecord::DisplayUsageInfo(){
	cout<<"\n(Readings: "<<prevReading<<","<<curReading<<"\t\t"<<"HV:";
	cout<<heatingValue<<" Rate: "<<rt<<" Supply Charge:"<<supplyCharge<<")"<<endl;
}
void GasBillRecord::UpdateBalance(){
	double C,P;
	C=curReading-prevReading; 
	P=supplyCharge*DaysSinceLastReading; 
	BillAmount=(C*heatingValue*rt)*Discount-getAccntBalance();
	setAccountBalance(0);
}
bool PhoneBillRecord::ReadUsageInfo(ifstream &fin){
	//cout<<"Phone"<<endl;
	fin>>noOflocalCalls>>localCallRt>>longDstTime>>longDstRt>>LineRental;
}
void PhoneBillRecord::DisplayUsageInfo(){
	cout<<"\n(LCalls:"<<noOflocalCalls<<","<<localCallRt<<"\t\t"<<"DCalls:";
	cout<<longDstTime<<","<<longDstRt<<"\t\t"<<"Rental:"<<LineRental<<")"<<endl;
}
void PhoneBillRecord::UpdateBalance(){
	double L,P,D;
	L=localCallRt*noOflocalCalls;
	D=longDstRt*longDstTime;
	P=LineRental*DaysSinceLastReading; 
	BillAmount=(L+D+P)*Discount-getAccntBalance(); 
	setAccountBalance(0);
}
