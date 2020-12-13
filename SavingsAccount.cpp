// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "SavingsAccount.h"
#include "CustomError.h"
#include <string>
using namespace std;

SavingsAccount::SavingsAccount(const string& name, const Date& date):Account(name, date) {
	setInterestRate(0.0);
}

SavingsAccount::SavingsAccount(const string& name, long accNum, double balance, const Date& open, const Date& close, double interest)
	:Account(name, accNum, balance, open, close) {
	setInterestRate(interest);
}

SavingsAccount& SavingsAccount::setInterestRate(double interest) {
	if (interest >= 0) {
		interestRate = interest;
	} else {
		interest = 0.05;
	}
	return *this;
}

double SavingsAccount::getInterestRate() const {
	return interestRate;
}

string SavingsAccount::toString() const {
	string parsed = "SavingsAccount," + getAccountHolder() + "," + to_string(getAccountNumber()) + "," + to_string(getBalance()) + ","
		 + getOpenedDate().toString() + "," + getClosedDate().toString() + "," + to_string(getInterestRate());
	return parsed;
}


double SavingsAccount::withdraw(double amount) {
	if (amount > getBalance()) {
		throw CustomError("Error: You do not have enough money!");
	} else if (amount <= 0) {
		throw CustomError("Error: Your withdrawal must be greater than $0.00");
	} else {
		setBalance(getBalance() - amount);
		return amount;
	}
}

double SavingsAccount::deposit(double amount) {
	double dep = amount + (amount * getInterestRate());
	if (amount <= 0) {
		throw CustomError("Error: Your deposit must be greater than $0.00");
	} else {
		setBalance(getBalance() + amount);
		return amount;
	}
}

double SavingsAccount::transfer(Account* acc, double amount) {
	if (amount <= 0) {
		throw CustomError("Error: Your transfer must be greater than $0.00");
	} else if (*acc == *this) {
		throw CustomError("Error: You cannot transfer into the same account!");
	} else {
		withdraw(amount);
		acc->setBalance(acc->getBalance() + amount);
		return amount;
	}
}

istream& SavingsAccount::input(istream& in) {
	double deposit;
	cout << "\t\t\t>>> Please Enter your Starting Deposit:" << endl;
	in >> deposit;
	while (in.fail()) {
		cout << "\t\t\t(!) Error: You entered a bad number! Try again (!)" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\t\t\t>>> Please Enter your Starting Deposit:" << endl;
		in >> deposit;
	}
	while (deposit < 25) {
		cout << "\t\t\t(!) Error: Your deposit must be at least $25.00" << endl;
		cout << "\t\t\t>>> Please Enter your Starting Deposit:" << endl;
		in >> deposit;
	}

	if (deposit >= 2500) {
		setInterestRate(0.05);
	} else {
		setInterestRate(0.02);
	}
	setBalance(deposit);
	return in;
}

ostream& SavingsAccount::print(ostream& out) const {
	out << "Account Type: Savings Account" << endl;
	Account::print(out);
	out << "Interest Rate: " << (getInterestRate() * 100) << "%" << endl;
	return out;
}
