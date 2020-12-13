// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef RETIREACCOUNT_H
#define RETIREACCOUNT_H

#include "Account.h"

class RetireAccount : public Account {

	private:
		double monthlyMinimum;
		Date retireDate;
	public:
		RetireAccount(double = 500.0, int = 0, const string& = "N/A", const Date& = Date::getTodayDate()); // Min Deposit | Years |
		RetireAccount(const string&, long, double, const Date&, const Date&, const Date&, double); // Used to read data from file
		RetireAccount(const string&, const Date & = Date::getTodayDate());
		 
		RetireAccount& setMonthlyMinimum(double);
		RetireAccount& setRetireDate(const Date&);
		RetireAccount& setRetireDate(int);

		double getMonthlyMinimum() const;
		Date getRetireDate() const;

		virtual double withdraw(double);
		virtual double deposit(double);
		virtual double transfer(Account*, double);

		virtual ostream& print(ostream&) const;
		virtual istream& input(istream&);

		virtual string toString() const;

};

#endif