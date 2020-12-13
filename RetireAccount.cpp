// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "RetireAccount.h"
#include "CustomError.h"
#include <string>
#include <iomanip>

RetireAccount::RetireAccount(double minimum, int years, const string& name, const Date& opened):Account(name, opened) {
	setMonthlyMinimum(minimum).setRetireDate(years);
}

RetireAccount::RetireAccount(const string& name, long accNum, double balance, const Date& open, const Date& close, const Date& retire, double min)
	:Account(name, accNum, balance, open, close) {
	setMonthlyMinimum(min).setRetireDate(retire);
}

RetireAccount::RetireAccount(const string& name, const Date& open) : Account(name, open) {
	setMonthlyMinimum(1.0).setRetireDate(open);
}

RetireAccount& RetireAccount::setMonthlyMinimum(double min) {
	if (min > 0) {
		monthlyMinimum = min;
	} else {
		monthlyMinimum = 500.0;
	}
	return *this;
}

RetireAccount& RetireAccount::setRetireDate(int year) {
	if (year <= Date::getTodayDate().getYear()) {
		retireDate.setDate(Date::getTodayDate().getMonth(), Date::getTodayDate().getDay(), Date::getTodayDate().getYear() + 65);
	} else {
		retireDate.setDate(Date::getTodayDate().getMonth(), Date::getTodayDate().getDay(), year);
	}
	return *this;
}

RetireAccount& RetireAccount::setRetireDate(const Date& date) {
	retireDate.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

double RetireAccount::getMonthlyMinimum() const {
	return monthlyMinimum;
}

Date RetireAccount::getRetireDate() const {
	return retireDate;
}


string RetireAccount::toString() const {
	string parsed = "RetireAccount," + getAccountHolder() + "," + to_string(getAccountNumber()) + "," + to_string(getBalance()) + "," +
		getOpenedDate().toString() + "," + getClosedDate().toString() + "," + getRetireDate().toString() + "," + to_string(getMonthlyMinimum());
	return parsed;
}


double RetireAccount::withdraw(double amount) {
	if (getRetireDate() > Date::getTodayDate()) {
		throw CustomError("Error: You cannot withdraw money until you retire! - " + getRetireDate().toString());
	} else if (amount > getBalance()) {
		throw CustomError("Error: You do not have enough money!");
	} else if (amount <= 0) {
		throw CustomError("Error: Your withdrawal must be greater than $0.00");
	} else {
		setBalance(getBalance() - amount);
		return amount;
	}
}

double RetireAccount::deposit(double amount) {
	if (amount < getMonthlyMinimum()) {
		throw CustomError("Error: You must deposit a minimum of $" + to_string(getMonthlyMinimum()));
	} else if (amount <= 0) {
		throw CustomError("Error: Your deposit must be greater than $0.00");
	} else {
		setBalance(getBalance() + amount);
		return amount;
	}
}

double RetireAccount::transfer(Account* acc, double amount) {
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

istream& RetireAccount::input(istream& in) {
	int years;
	double minimum;
	cout << "\t\t\t>>> Enter the Year you plan to retire in: " << endl;
	in >> years;

	cout << "\t\t\t>>> Enter your desired Monthly Minimum Deposit: " << endl;
	in >> minimum;

	while (in.fail()) {
		cout << "(!) Error: You entered a bad number! Try again (!)" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\t\t\t>>> Enter the Year you plan to retire in: " << endl;
		in >> years;

		cout << "\t\t\t>>> Enter your desired Monthly Minimum Deposit: " << endl;
		in >> minimum;
	}

	while (years <= Date::getTodayDate().getYear()) {
		cout << "\t\t\t(!) Error: Please enter a year greater than " << Date::getTodayDate().getYear() << endl;
		in >> years;
	}

	while (minimum < 1) {
		cout << "\t\t\t(!) Error: Please enter a minimum monthly deposit that is greater than 0!" << endl;
		in >> minimum;
	}

	setRetireDate(years).setMonthlyMinimum(minimum);
	return in;
}

ostream& RetireAccount::print(ostream& out) const {
	out << "Account Type: Retire Account" << endl;
	Account::print(out);
	out << fixed << setprecision(2) << "Monthly Minimum Deposit: $" << getMonthlyMinimum() << endl;
	out << "Retire Date Date: " << getRetireDate() << endl;
	return out;
}
