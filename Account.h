// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Date.h"
#include <vector>

class Account {

	friend istream& operator>>(istream&, Account&);
	friend ostream& operator<<(ostream&, const Account&);

	private:
		static vector<long> accountNumbers;

		string accountHolder;
		long accountNumber;
		double balance;
		Date openDate;
		Date closeDate;

		bool contains(long);
		void setAccountNumber();
	public:
		Account(const string&, long, double, const Date&, const Date&); // Used to read data from file
		Account(const string&, const Date& = Date::getTodayDate()); // Name | Open Date

		Account& setAccountHolder(const string&);
		Account& setBalance(double);
		Account& setOpenDate(const Date&);
		Account& setCloseDate(const Date&);

		string getAccountHolder() const;
		long getAccountNumber() const;
		double getBalance() const;
		Date getOpenedDate() const;
		Date getClosedDate() const;

		bool operator==(const Account&);

		virtual ostream& print(ostream&) const;
		virtual istream& input(istream&);

		virtual double withdraw(double) = 0;
		virtual double deposit(double) = 0;
		virtual double transfer(Account*, double) = 0;

		virtual string toString() const = 0;
		

};

#endif