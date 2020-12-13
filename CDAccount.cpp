// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "CDAccount.h"
#include "CustomError.h"
#include <iomanip>
#include <iostream>
using namespace std;

CDAccount::CDAccount(int years, double interest, double min, const string& name, const Date& date):Account(name, date) {
	setMaturityDate(years).setInterestRate(interest).setMinimumWithdrawBal(min);
}

CDAccount::CDAccount(const string& name, long accNum, double balance, const Date& open, const Date& close, double interest, double min, const Date& mature)
	:Account(name, accNum, balance, open, close) {
	setMaturityDate(mature).setInterestRate(interest).setMinimumWithdrawBal(min);
}

CDAccount::CDAccount(const string& name, const Date& date):Account(name, date) {
	setInterestRate(0.00).setMinimumWithdrawBal(0.00);
}

CDAccount& CDAccount::setInterestRate(double interest) {
	if (interest >= 0) {
		interestRate = interest;
	} else {
		interestRate = 0.05;
	}
	return *this; 
}

CDAccount& CDAccount::setMinimumWithdrawBal(double bal) {
	if (bal > 0) {
		minAmountWithdraw = bal;
	} else {
		minAmountWithdraw = 500000.0;
	}
	return *this;
}

CDAccount& CDAccount::setMaturityDate(const Date& date) {
	maturityDate.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

CDAccount& CDAccount::setMaturityDate(int years) {
	maturityDate.setDate(Date::getTodayDate().getMonth(), Date::getTodayDate().getDay(), Date::getTodayDate().getYear() + years);
	return *this;
}

double CDAccount::getInterestRate() const {
	return interestRate;
}

double CDAccount::getMinWithdrawBal() const {
	return minAmountWithdraw;
}

double CDAccount::getMinimumDepositAmount() const {
	return minDepositAmount;
}

Date CDAccount::getMaturityDate() const {
	return maturityDate;
}

string CDAccount::toString() const {
	string parsed = "CDAccount," + getAccountHolder() + "," + to_string(getAccountNumber()) + "," + to_string(getBalance()) + "," 
		+ getOpenedDate().toString() + "," + getClosedDate().toString() + "," + getMaturityDate().toString() + "," + to_string(getInterestRate())
		+ "," + to_string(getMinWithdrawBal());
	return parsed;
}


double CDAccount::withdraw(double amount) {
	if (maturityDate > Date::getTodayDate()) {
		throw CustomError("Error: Your CD Account has not matured yet! You can withdraw on " + getMaturityDate().toString());
	} else if (getBalance() < getMinWithdrawBal()) {
		throw CustomError("Error: Your CD must have a minimum of $" + to_string(getMinWithdrawBal()) + "to withdraw!");
	} else if (amount > getBalance()) {
		throw CustomError("Error: You do not have enough money!");
	} else if (amount <= 0) {
		throw CustomError("Error: Your withdrawal must be greater than $0.00!");
	} else {
		setBalance(getBalance() - amount);
		return amount;
	}
}

double CDAccount::deposit(double amount) {
	double dep = amount + (amount * getInterestRate());
	if (amount < getMinimumDepositAmount()) {
		throw CustomError("Error: You must deposit a minimum of $" + to_string(getMinimumDepositAmount()));
	} else if (amount <= 0) {
		throw CustomError("Error: Your deposit must be greater than $0.00!");
	} else if (getMaturityDate() > Date::getTodayDate()) {
		throw CustomError("Error: You cannot deposit money until maturity date!");
	} else {
		setBalance(getBalance() + dep);
		return amount;
	}
}

double CDAccount::transfer(Account* acc, double amount) {
	if (amount <= 0) {
		throw CustomError("Error: Your deposit must be greater than $0.00!");
	} else if (*acc == *this) {
		throw CustomError("Error: You cannot transfer into the same account!");
	} else {
		withdraw(amount);
		acc->setBalance(acc->getBalance() + amount);
		return amount;
	}

}

istream& CDAccount::input(istream& in) {
	int years;
	double minimum, deposit;
	cout << "\t\t\t>>> Enter the Amount of Years for the CD: " << endl;
	in >> years;

	cout << "\t\t\t>>> Enter the desired Minimum Withdraw Balance to be:" << endl;
	in >> minimum;

	cout << "\t\t\t>>> Enter the desired Deposit Amount: (Minimum is $2,500)" << endl;
	in >> deposit;

	while (in.fail()) {
		cout << "\t\t\t (!) Error: You entered a bad number! Try again (!)" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\t\t\t>>> Enter the Amount of Years for the CD: " << endl;
		in >> years;

		cout << "\t\t\t>>> Enter the desired Minimum Withdraw Balance to be:" << endl;
		in >> minimum;

		cout << "\t\t\t>>> Enter the desired Deposit Amount: (Minimum is $2,500)" << endl;
		in >> deposit;
	}

	while (years < 1) {
		cout << "\t\t\t (!) Error: Your CD must be set for a minimum of 1 year!" << endl;
		in >> years;
	}
	while (minimum <= 2500) {
		cout << "\t\t\t (!) Error: The set minimum withdraw balance must be greater than $2,500" << endl;
		in >> minimum;
	}

	if (deposit >= 5000) {
		setInterestRate(0.05);
	} else {
		setInterestRate(0.03);
	}

	setMaturityDate(years).setMinimumWithdrawBal(minimum);
	setBalance(deposit);
	return in;
}

ostream& CDAccount::print(ostream& out) const {
	out << "Account Type: CD Account" << endl;
	Account::print(out);
	out << "Interest Rate: " << (getInterestRate() * 100) << "%" << endl;
	out << "Maturity Date: " << getMaturityDate() << endl;
	out << fixed << setprecision(2) << "Minimum Deposit: $" << getMinimumDepositAmount() << " | Minimum Withdraw: $" << getMinWithdrawBal() << endl;
	return out;
}
