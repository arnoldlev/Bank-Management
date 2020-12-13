// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "Loans.h"
#include "CustomError.h"
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

Loans::Loans(double loaned, double remain, double intRate, double monthly, int term, LoanType type, const Date& bill, const Date& open) {
	setLoanedAmount(loaned).setRemainingBalance(remain).setInterestRate(intRate).setYearTerms(term).setType(type).setMonthlyPayment(monthly);
	setBillDate(bill).setStartDate(open);
}

Loans::Loans(int term, double loan, LoanType type, const Date& opened) {
	setRemainingBalance(loan);
	setType(type).setStartDate(opened).setYearTerms(term).setLoanedAmount(loan);
	setInterestRate(generateInterestRate());
	setMonthlyPayment(generateMonthlyPayment());
	generateBill();
}

double Loans::generateMonthlyPayment() {
	int n = 12 * getYearTerm();
	double rate = getInterestRate() / 12;
	double discount = (pow(1 + rate, n) - 1) / (pow(1 + rate, n)* rate);
	return getLoanedAmount() / discount;
}

double Loans::generateInterestRate() {
	if (getYearTerm() <= 5) {
		return 0.025;
	} else if (getYearTerm() >= 6 && getYearTerm() <= 10) {
		return 0.023;
	} else {
		return 0.02;
	}
}

void Loans::generateBill() {
	billDate = getStartDate().addMonth(1);
}

Loans& Loans::setLoanedAmount(double amount) {
	if (amount > 0) {
		loanedAmount = amount;
	} else {
		loanedAmount = 0.0;
	}
	return *this;
}

Loans& Loans::setRemainingBalance(double remain) {
	if (remain >= 0) {
		remainingBalance = remain;
	} else {
		remainingBalance = 0.0;
	}
	return *this;
}

Loans& Loans::setInterestRate(double interest) {
	if (interest >= 0) {
		this->interest = interest;
	} else {
		this->interest = 0.0;
	}
	return *this;
}

Loans& Loans::setMonthlyPayment(double pay) {
	if (pay >= 0) {
		monthlyPayment = pay;
	} else {
		monthlyPayment = 0.0;
	}
	return *this;
}

Loans& Loans::setYearTerms(int years) {
	if (years > 0) {
		termInYears = years;
	} else {
		termInYears = 0;
	}
	return *this;
}

Loans& Loans::setType(LoanType type) {
	typeOfLoan = type;
	return *this;
}

Loans& Loans::setBillDate(const Date& date) {
	billDate.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

Loans& Loans::setStartDate(const Date& date) {
	startDate.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

double Loans::getInterestRate() const {
	return interest;
}

double Loans::getLoanedAmount() const {
	return loanedAmount;
}

double Loans::getRemainingBalance() const {
	return remainingBalance;
}

double Loans::getMonthlyPayment() const {
	return monthlyPayment;
}

int Loans::getYearTerm() const {
	return termInYears;
}

LoanType Loans::getLoanType() const {
	return typeOfLoan;
}

string Loans::getLoanTypeString() const {
	if (typeOfLoan == LoanType::PERSONAL) {
		return "Personal";
	} else if (typeOfLoan == LoanType::HOME) {
		return "Home";
	} else {
		return "Student";
	}
}

Date Loans::getBillDue() const {
	return billDate;
}

Date Loans::getStartDate() const {
	return startDate;
}

bool Loans::checkAmount(int score) {
	double amount = getLoanedAmount();
	if (getLoanType() == LoanType::STUDENT) {
		if (amount <= 70000) {
			return true;
		}
	} else {
		if (score >= 500 && score < 600) {
			if (amount <= 500000 && getLoanType() == LoanType::HOME) {
				return true;
			} else if (amount <= 10000 && getLoanType() == LoanType::PERSONAL) {
				return true;
			}
		} else if (score >= 600 && score < 700) {
			if (amount <= 600000 && getLoanType() == LoanType::HOME) {
				return true;
			}
			else if (amount <= 25000 && getLoanType() == LoanType::PERSONAL) {
				return true;
			}
		} else if (score >= 700 && score < 800) {
			if (amount <= 900000 && getLoanType() == LoanType::HOME) {
				return true;
			}
			else if (amount <= 50000 && getLoanType() == LoanType::PERSONAL) {
				return true;
			}
		} else if (score >= 800) {
			if (amount <= 1500000 && getLoanType() == LoanType::HOME) {
				return true;
			}
			else if (amount <= 100000 && getLoanType() == LoanType::PERSONAL) {
				return true;
			}
		}
	}
	return false;
}

double Loans::makePayment(double amount, Account* acc) {
	if (amount > getRemainingBalance()) {
		throw CustomError("Error: You cannot pay more than your remaining balance!");
	} else if (amount < getMonthlyPayment()) {
		throw CustomError("Error: You must pay a minimum of $" + to_string(getMonthlyPayment()));
	} else if (getBillDue() > Date::getTodayDate()) {
		throw CustomError("Error: You cannot make early payments on Loans!");
	} else {
		if (getBillDue() == Date::getTodayDate()) {
			acc->withdraw(amount);
			setRemainingBalance(getRemainingBalance() - amount);
			setBillDate(getBillDue().addMonth(1));
			return amount;
		} else if (getBillDue() < Date::getTodayDate()) {
			acc->withdraw(amount + 25);
			setRemainingBalance(getRemainingBalance() - amount);
			setBillDate(getBillDue().addMonth(1));
			return amount + 25;
		} 
	}
	return 0.0;
}

string Loans::toString() const {
	string parsed = to_string(getLoanedAmount()) + "," + to_string(getRemainingBalance()) + "," + to_string(getInterestRate())
		+ "," + to_string(getMonthlyPayment()) + "," + to_string(getYearTerm()) + "," + getLoanTypeString() + "," + getBillDue().toString() + "," + getStartDate().toString();
	return parsed;
}

LoanType Loans::parse(int type) {
	if (type == 1) {
		return LoanType::PERSONAL;
	}
	else if (type == 2) {
		return LoanType::HOME;
	}
	else {
		return LoanType::STUDENT;
	}
}

LoanType Loans::parse(const string& type) {
	if (type == "Personal") {
		return LoanType::PERSONAL;
	} else if (type == "Home") {
		return LoanType::HOME;
	} else {
		return LoanType::STUDENT;
	}
}

ostream& operator<<(ostream& out, const Loans& loan) {
	out << "Loan Type: " << loan.getLoanTypeString() << endl;
	out << fixed << setprecision(2) << "Amount Loaned: $" << loan.getLoanedAmount() << " | Remaining Balance: $" << loan.getRemainingBalance() << endl;
	out << fixed << setprecision(1) << "Interest Rate: " << loan.getInterestRate() * 100 << "%" << endl;
	out << fixed << setprecision(2) << "Next Payment Due: " << loan.getBillDue() << " | Minimum Payment: $" << loan.getMonthlyPayment() << endl;
	out << "Loan Issued: " << loan.getStartDate() << endl;
	return out;
}