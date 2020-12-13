// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "CreditCard.h"
#include "CustomError.h"
#include <string>
#include <iomanip>
using namespace std;

CreditCard::CreditCard(double maxAmount, const Date& opened, const string& name):Card(name, CardType::CREDIT) {
	setMaxAmount(maxAmount).setOpenDate(opened);
	setAvaliableBalance(maxAmount).setBalanceDue(0.00);
	generateBill();
}

CreditCard::CreditCard(const string& name, CardType type, double maxAmount, double balDue, double avalBal, const Date& open, const Date& bill)
	:Card(name, type, maxAmount) {
	setMaxAmount(maxAmount).setBalanceDue(balDue).setAvaliableBalance(avalBal).setOpenDate(open).setBillDueDate(bill);
}

void CreditCard::generateBill() {
	billDate = getOpenedDate().addMonth(1);
}

CreditCard& CreditCard::setMaxAmount(double max) {
	if (max > 0) {
		maxAmount = max;
	} else {
		maxAmount = 500.0;
	}
	return *this;
}

CreditCard& CreditCard::setBalanceDue(double bal) {
	if (bal >= 0) {
		balanceDue = bal;
	} else {
		balanceDue = 0.00;
	}
	return *this;
}

CreditCard& CreditCard::setAvaliableBalance(double bal) {
	if (bal >= 0) {
		avaliableBalance = bal;
	} else {
		avaliableBalance = 0.00;
	}
	return *this;
}

CreditCard& CreditCard::setBillDueDate(const Date& date) {
	billDate.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

CreditCard& CreditCard::setOpenDate(const Date& date) {
	openDate.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

double CreditCard::getMaxAmount() const {
	return maxAmount;
}

double CreditCard::getAvaliableBalance() const {
	return avaliableBalance;
}

double CreditCard::getBalanceDue() const {
	return balanceDue;
}

double CreditCard::getMinimumPayment() const {
	return MINIMUM_PAYMENT;
}

double CreditCard::getAPR() const {
	return APR;
}

Date CreditCard::getBillDueDate() const {
	return billDate;
}

Date CreditCard::getOpenedDate() const {
	return openDate;
}

double CreditCard::makePayment(double amount, Account* acc) {
	double totalAmount = (amount == getBalanceDue()) ? amount : amount + (amount * (getAPR() / 365));
	if (amount > getBalanceDue()) {
		throw CustomError("Error: You cannot pay more than your due balance!");
	} else if (amount > getMaxAmount()) {
		throw CustomError("Error: You cannot pay more than your maximum limit!");
	} else if (amount < getMinimumPayment()) {
		throw CustomError("Error: You must pay a minimum of $25!");
	} else {
		if (getBillDueDate() == Date::getTodayDate()) {
			acc->withdraw(totalAmount);
			setAvaliableBalance(getAvaliableBalance() + amount);
			setBalanceDue(getBalanceDue() - amount);
			billDate = billDate.addMonth(1);
			return totalAmount;
		} else if (getBillDueDate() < Date::getTodayDate()) {
			acc->withdraw(totalAmount + 25);
			setAvaliableBalance(getAvaliableBalance() + amount);
			setBalanceDue(getBalanceDue() - amount);
			billDate = billDate.addMonth(1);
			return totalAmount + 25;
		} else {
			acc->withdraw(totalAmount);
			setAvaliableBalance(getAvaliableBalance() + amount);
			setBalanceDue(getBalanceDue() - amount);
			return totalAmount;
		}
	}
}

bool CreditCard::transact(double amount) {
	if (amount > getAvaliableBalance()) {
		return false;
	} else {
		setAvaliableBalance(getAvaliableBalance() - amount);
		setBalanceDue(getBalanceDue() + amount);
		return true;
	}
}

ostream& CreditCard::printInfo(ostream& out) const {
	out << fixed << setprecision(2) << "Maximum Amount: $" << getMaxAmount() << endl;
	out << "Avaliable Balance $" << getAvaliableBalance() << " | Balance Due: $" << getBalanceDue() << endl;
	out << "Bill Due Date: " << getBillDueDate() << " | Opened Date: " << getOpenedDate() << endl;
	Card::printInfo(out);
	return out;
}

string CreditCard::toString() const {
	string info = getName() + "," + getCardNumber() + "," + to_string(getSecurityCode()) + "," + getExpireDate().toString() + "," 
		+ to_string(getMaxAmount()) + "," + to_string(getBalanceDue()) + "," + to_string(getAvaliableBalance()) + "," 
		+ getOpenedDate().toString() + "," + getBillDueDate().toString();
	return info;
}