/**********************************************************************
 * BillRecord.h - CSCI251 - Ass4 - BillRecord class declaration
 * <NIMRA GAUHAR> <5949403> <12/24/2018>
 **********************************************************************/
#ifndef BILLRECORD_H
#define BILLRECORD_H

#include <string>
using namespace std;

enum BillType {eElect, eGas, ePhone };

// base class...

class BillRecord {
  public:
	BillRecord();
	bool ReadCustDetails(ifstream &fin);
	virtual bool ReadUsageInfo(ifstream &fin);
	void DisplayCustDetails();
	virtual void DisplayUsageInfo();
	virtual void UpdateBalance()=0;
	//some important setters and getters
	void setBType(int n);
	void SetDiscount(float d);
	string getSupplier();
	string getName();
	string getBType();
	string getAddress();
	double getAccntBalance();
	double getBillAmount();
	float getDiscount();
	void setAccountBalance(double d);


  private:
  	BillType BType;	//BillType:eElect,eGas,ePhone
	string Supplier; // Supplier's name
	string Name, Address; // Customer's name and address
	double AccountBalance; // Customer's account balance
  protected:
	int DaysSinceLastReading; // Days since last reading
	double BillAmount;// Amount in dollars and cents of this bill
	float Discount;
};

//derived classes...
class ELectBillRecord:public BillRecord{
	private:
		double prevReading,curReading,rt1,rt1Threshold,rt2,supplyCharge;
	public:
		bool ReadUsageInfo(ifstream &fin);
 		void DisplayUsageInfo();
 		void UpdateBalance();
};
class GasBillRecord:public BillRecord{
	private:
		double prevReading,curReading,heatingValue,rt,supplyCharge;
	public:
		bool ReadUsageInfo(ifstream &fin);
		void DisplayUsageInfo();
 		void UpdateBalance();
};
class PhoneBillRecord:public BillRecord{
	private:
		double noOflocalCalls,localCallRt,longDstTime,longDstRt,LineRental;
	public:	
		bool ReadUsageInfo(ifstream &fin);
 		void DisplayUsageInfo();
		void UpdateBalance();
};


#endif

