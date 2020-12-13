// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"
#include "DebitCard.h"
using namespace std;

class CheckingAccount : public Account {
	private:
		DebitCard card;
		double atmLimit;
		double monthlyCharge;
	public:
		CheckingAccount(const string&, long, double, const Date&, const Date&, double, double, double); // Used for reading file data
		CheckingAccount(double = 1000.00, double = 25.00, const string& = "N/A", const Date& = Date::getTodayDate()); //ATM Limit, Monthly Charge, Date open 
		CheckingAccount(const string & = "N/A", const Date & = Date::getTodayDate());

		CheckingAccount& setATMLimit(double);
		CheckingAccount& setMonthlyCharge(double);
		CheckingAccount& setMonthlyCharge(const Date&);
		CheckingAccount& setDebitCard(const string&, int, const Date&);

		double getATMLimit() const;
		double getMonthlyCharge() const;
		const DebitCard& getDebitCard() const;

		virtual double withdraw(double);
		virtual double deposit(double);
		virtual double transfer(Account*, double);

		virtual ostream& print(ostream&) const;
		virtual istream& input(istream&);

		virtual string toString() const;

};

#endif