// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "Card.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
using namespace std;

vector<string> Card::cardNumbers;

Card::Card(const string& full, CardType type, double max) {
	setName(full);
	this->type = type;
}

Card::Card(const string& full, CardType type) {
	setName(full);
	this->type = type;
	generateCard();
}

// Algorithm of generating a valid card number found online for performance boost! 
// Checking if a card number exists, security code, expire date and utility functions custom made by me
void Card::generateCard() {
	srand((unsigned int)time(NULL));

	setCVC(rand() % 300 + 100);
	expireDate.setDate(Date::getTodayDate().getMonth(), Date::getTodayDate().getDay(), Date::getTodayDate().getYear() + 5); 

	int check[15] = { 0 };
	for (int i = 14; i >= 0; i--) {
		cardNumber[i] = rand() % 9;
		check[i] = (cardNumber[i] * (((i + 1) % 2) + 1)) % 9;
	}
	cardNumber[15] = (sum(check) * 9) % 10;

	while (contains(getCardNumber())) {
		int doubleCheck[15] = { 0 };
		for (int i = 14; i >= 0; i--) {
			cardNumber[i] = rand() % 9;
			doubleCheck[i] = (cardNumber[i] * (((i + 1) % 2) + 1)) % 9;
		}
		cardNumber[15] = (sum(doubleCheck) * 9) % 10;
	}

	cardNumbers.push_back(getCardNumber());
}

bool Card::contains(const string& number) {
	for (int i = 0; i < (int) cardNumbers.size(); i++) {
		if (cardNumbers[i] == number) {
			return true;
		}
	}
	return false;
}

int Card::sum(int nums[]) {
	int total = 0;
	for (int i = 0; i < 15; i++) {
		total += nums[i];
	}
	return total;
}

Card& Card::setName(const string& name) {
	if (name.length() > 1) {
		this->name = name;
	} else {
		this->name = "N/A";
	}
	return *this;
}

Card& Card::setCardNumber(const string& num) {
	if (num.length() == 16) {
		for (int i = 0; i < (int) num.length(); i++) {
			int element = num[i] - '0';
			cardNumber[i] = element;
		}
	}
	return *this;
}

Card& Card::setCVC(int code) {
	securityCode = code;
	return *this;
}

Card& Card::setExpireDate(const Date& expire) {
	expireDate.setDate(expire.getMonth(), expire.getDay(), expire.getYear());
	return *this;
}

string Card::getCardNumber() const {
	string number = "";
	for (int i = 0; i < 16; i++) {
		number += to_string(cardNumber[i]);
	}
	return number;
}

string Card::getName() const {
	return name;
}

int Card::getSecurityCode() const {
	return securityCode;
}

Date Card::getExpireDate() const {
	return expireDate;
}

CardType Card::getType() const {
	return type;
}

bool Card::operator==(const Card& card) {
	if (card.getCardNumber() == getCardNumber()) {
		return true;
	}
	return false;
}

ostream& Card::printInfo(ostream& out) const {
	out << "\tCardHolder Name: " << getName() << endl;
	out << "\tExpiration Date: " << getExpireDate() << " | CVC: " << getSecurityCode() << endl;
	out << "\tCard Number: " << getCardNumber() << endl;
	return out;
}

ostream& operator<<(ostream& out, const Card& c) {
	return c.printInfo(out);
}