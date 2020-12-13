// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "Account.h"
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<long> Account::accountNumbers;

Account::Account(const string& name, long accountNum, double balance, const Date& open, const Date& close) {
	setAccountHolder(name).setBalance(balance).setOpenDate(open).setCloseDate(close);
	accountNumber = accountNum;
	accountNumbers.push_back(getAccountNumber());
}

Account::Account(const string& name, const Date& open) {
	setAccountHolder(name).setOpenDate(open).setBalance(0.00);
	setAccountNumber();
}

void Account::setAccountNumber() {
	accountNumber = 0;
	srand((unsigned int)time(NULL));
	for (int i = 1; i <= 15; i++) {
		accountNumber += rand() % 2500 + 1500;
	}
	while (contains(accountNumber)) {
		for (int i = 1; i <= 15; i++) {
			accountNumber += rand() % 2500 + 1500;
		}
	}
	accountNumbers.push_back(accountNumber);
}

bool Account::contains(long num) {
	for (int i = 0; i < (int)accountNumbers.size(); i++) {
		if (accountNumbers[i] == num) {
			return true;
		}
	}
	return false;
}

Account& Account::setAccountHolder(const string& name) {
	if (name.length() > 0) {
		accountHolder = name; 
	} else {
		accountHolder = "N/A";
	}
	return *this;
}
 
Account& Account::setBalance(double bal) {
	if (bal >= 0) {
		balance = bal;
	}
	return *this;
}

Account& Account::setOpenDate(const Date& start) {
	openDate.setDate(start.getMonth(), start.getDay(), start.getYear());
	return *this;
}

Account& Account::setCloseDate(const Date& close) {
	closeDate.setDate(close.getMonth(), close.getDay(), close.getYear());
	return *this;
}

string Account::getAccountHolder() const {
	return accountHolder;
}

long Account::getAccountNumber() const {
	return accountNumber;
}

double Account::getBalance() const {
	return balance;
}

Date Account::getOpenedDate() const {
	return openDate;
}

Date Account::getClosedDate() const {
	return closeDate;
}

bool Account::operator==(const Account& acc) {
	if (accountNumber == acc.getAccountNumber()) {
		return true;
	}
	return false;
}

ostream& operator<<(ostream& out, const Account& acc) {
	return acc.print(out);
}

istream& operator>>(istream& in, Account& acc) {
	return acc.input(in);
}

istream& Account::input(istream& in) {
	return in;
}

ostream& Account::print(ostream& out) const {
	out << "Account Number: " << getAccountNumber() << endl;
	out << fixed << setprecision(2) << "Avaliable Balance: $" << getBalance() << endl;
	if (getClosedDate().getYear() == 1990) {
		out << "Date Opened: " << getOpenedDate() << endl;
	} else {
		out << "Date Opened: " << getOpenedDate() << " | Date Closed: " << getClosedDate() << endl;
	}
	return out;
}