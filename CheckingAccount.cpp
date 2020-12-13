// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "CheckingAccount.h"
#include "CustomError.h"
#include <iomanip>
#include <cmath>
using namespace std;

CheckingAccount::CheckingAccount(const string& name, long accNum, double balance, const Date& open, const Date& close, double monthly, double atm, double max)
	:Account(name, accNum, balance, open, close),card(name, CardType::DEBIT, max, true) {
	setATMLimit(atm).setMonthlyCharge(monthly);
}

CheckingAccount::CheckingAccount(double atm, double monthly, const string& name, const Date& opened):Account(name, opened) {
	card.setName(name);
	setATMLimit(atm).setMonthlyCharge(monthly);
}

CheckingAccount::CheckingAccount(const string& name, const Date& opened):Account(name, opened) {
	card.setName(name);
	setATMLimit(1.0).setMonthlyCharge(1.0);
}

CheckingAccount& CheckingAccount::setDebitCard(const string& num, int cvc, const Date& expire) {
	card.setCardNumber(num).setCVC(cvc).setExpireDate(expire);
	return *this;
}

CheckingAccount& CheckingAccount::setMonthlyCharge(double ch) {
	if (ch >= 0) {
		monthlyCharge = ch;
	} else {
		monthlyCharge = 25.00;
	}
	return *this;
}

CheckingAccount& CheckingAccount::setMonthlyCharge(const Date& date) {
	Date today = Date::getTodayDate();
	int month = (today.getMonth() - date.getMonth()) + 12 * (today.getYear() - date.getYear());
	if (abs(month) >= 1) {
		setMonthlyCharge(15.00);
	} else {
		setMonthlyCharge(25.00);
	}
	return *this;
}

CheckingAccount& CheckingAccount::setATMLimit(double limit) {
	if (limit > 0) {
		atmLimit = limit;
	} else {
		atmLimit = 1000.0;
	}
	return *this;
}

double CheckingAccount::getATMLimit() const {
	return atmLimit;
}

double CheckingAccount::getMonthlyCharge() const {
	return monthlyCharge;
}

const DebitCard& CheckingAccount::getDebitCard() const {
	return card;
}

string CheckingAccount::toString() const {
	string parsed = "CheckingAccount," + getAccountHolder() + "," + to_string(getAccountNumber()) + "," + to_string(getBalance()) + "," 
		+ getOpenedDate().toString() + "," + getClosedDate().toString() + "," + to_string(getMonthlyCharge()) + "," + to_string(getATMLimit()) 
		+ "," + getDebitCard().toString();
	return parsed;
}

double CheckingAccount::withdraw(double amount) {
	if (amount > getATMLimit()) {
		throw CustomError("Error: You can only withdraw a maximum of $" + to_string(getATMLimit()));
	} else if (amount > getBalance()) {
		throw CustomError("Error: You do not have enough money!");
	} else if (amount <= 0) {
		throw CustomError("Error: Your withdrawal must be greater than $0.00!");
	} else {
		setBalance(getBalance() - amount);
		return amount;
	}
}

double CheckingAccount::deposit(double amount) {
	if (amount <= 0) {
		throw CustomError("Error: Your deposit must be greater than $0.00!");
	} else {
		setBalance(getBalance() + amount);
		return amount;
	}
}

double CheckingAccount::transfer(Account* acc, double amount) {
	if (amount > getBalance()) {
		throw CustomError("Error: You do not have enough money!");
	} else if (amount <= 0) {
		throw CustomError("Error: Your transfer must be greater than $0.00!");
	} else if (*acc == *this) {
		throw CustomError("Error: You cannot transfer into the same account!");
	} else {
		setBalance(getBalance() - amount);
		acc->setBalance(acc->getBalance() + amount);
		return amount;
	}
}

istream& CheckingAccount::input(istream& in) {
	double limit;
	cout << "\t\t\t>>> Please enter your desired ATM Withdraw Limit: " << endl;
	in >> limit;
	while (in.fail()) {
		cout << "\t\t\t(!) Error: You entered a bad number! Try again (!)" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\t\t\t>>> Please enter your desired ATM Withdraw Limit: " << endl;
		in >> limit;
	}
	while (limit <= 0) {
		cout << "\t\t\t(!) Error: Please enter a value greater than $0!" << endl;
		in >> limit;
	}
	setATMLimit(limit);
	cout << "\t\t\t>>> Please enter your desired Debit Card Transacation Limit: " << endl;
	in >> limit;
	while (limit <= 0) {
		cout << "\t\t\t(!) Error: Please enter a value greater than $0!" << endl;
		in >> limit;
	}
	this->card.setMaxSpendAmount(limit);
	return in;
}

ostream& CheckingAccount::print(ostream& out) const {
	out << "Account Type: Checking Account" << endl;
	Account::print(out);
	out << fixed << setprecision(2) << "Monthly Charge: $" << getMonthlyCharge() << endl;
	out << fixed << setprecision(2) << "ATM Withdraw Limit: $" << getATMLimit() << endl;
	out << "Debit Card Associated: " << endl;
	out << getDebitCard();
	return out;
}
