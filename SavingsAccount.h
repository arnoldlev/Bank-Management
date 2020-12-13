// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
	private:
		double interestRate;
	public:
		SavingsAccount(const string & = "N/A", const Date& = Date::getTodayDate()); //| Name | Open Date
		SavingsAccount(const string&, long, double, const Date&, const Date&, double); // Used to read data from file

		SavingsAccount& setInterestRate(double);
		double getInterestRate() const;

		virtual double withdraw(double);
		virtual double deposit(double);
		virtual double transfer(Account*, double);

		virtual ostream& print(ostream&) const;
		virtual istream& input(istream&);

		virtual string toString() const;
};

#endif