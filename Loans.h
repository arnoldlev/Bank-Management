// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef LOANS_H
#define LOANS_H

#include "LoanType.h"
#include "Account.h"

class Loans {
	friend ostream& operator<<(ostream&, const Loans&); 

	private:
		double loanedAmount;
		double remainingBalance;
		double interest;
		double monthlyPayment;
		int termInYears;
		LoanType typeOfLoan;
		Date billDate;
		Date startDate;

		double generateMonthlyPayment();
		double generateInterestRate();
		void generateBill();
	public:
		Loans(double, double, double, double, int, LoanType, const Date&, const Date&); // Used for reading data from file
		Loans(int, double, LoanType, const Date & = Date::getTodayDate()); // Term, Loan, Type, Open Date

		Loans& setLoanedAmount(double);
		Loans& setRemainingBalance(double);
		Loans& setInterestRate(double);
		Loans& setMonthlyPayment(double);
		Loans& setYearTerms(int);
		Loans& setType(LoanType);
		Loans& setBillDate(const Date&);
		Loans& setStartDate(const Date&);

		static LoanType parse(int);
		static LoanType parse(const string&);

		double getInterestRate() const;
		double getLoanedAmount() const;
		double getRemainingBalance() const;
		double getMonthlyPayment() const;
		int getYearTerm() const;
		LoanType getLoanType() const;
		string getLoanTypeString() const;
		Date getBillDue() const;
		Date getStartDate() const;

		bool checkAmount(int);
		double makePayment(double, Account*);
		string toString() const;
};

#endif