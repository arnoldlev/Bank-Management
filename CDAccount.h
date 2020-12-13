// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef CDACCOUNT_H
#define CDACCOUNT_H

#include "Account.h"

class CDAccount : public Account {
	private:
		const double minDepositAmount = 2500.0;
		double interestRate;
		double minAmountWithdraw;
		Date maturityDate;
	public:
		CDAccount(int = 4, double = 0.05, double = 500000.0, const string& = "N/A", const Date& = Date::getTodayDate()); // Term in Years | Interest Rate | Minimum Amount To withdraw | Name | Date
		CDAccount(const string&, long, double, const Date&, const Date&, double, double, const Date&); // Used for reading data from file
		CDAccount(const string & = "N/A", const Date & = Date::getTodayDate());

		CDAccount& setInterestRate(double);
		CDAccount& setMinimumWithdrawBal(double);
		CDAccount& setMaturityDate(int);
		CDAccount& setMaturityDate(const Date&);

		double getInterestRate() const;
		double getMinWithdrawBal() const;
		double getMinimumDepositAmount() const;
		Date getMaturityDate() const;

		virtual double withdraw(double);
		virtual double deposit(double);
		virtual double transfer(Account*, double);

		virtual ostream& print(ostream&) const;
		virtual istream& input(istream&);

		virtual string toString() const;
};


#endif