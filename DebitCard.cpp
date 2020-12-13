// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "DebitCard.h"
#include <string>
using namespace std;

DebitCard::DebitCard(const string& name, CardType type, double max):Card(name, type) {
	setMaxSpendAmount(max);
}

DebitCard::DebitCard(const string& name, CardType type, double maxSpend, bool load):Card(name, type, maxSpend) {
	setMaxSpendAmount(maxSpend);
}

DebitCard& DebitCard::setMaxSpendAmount(double max) {
	if (max > 0) {
		maxSpendAmount = max;
	} else {
		maxSpendAmount = 1000;
	}
	return *this;
}

double DebitCard::getMaxSpendAmount() const {
	return maxSpendAmount;
}

ostream& DebitCard::printInfo(ostream& out) const {
	Card::printInfo(out);
	out << "\tMaximum Transaction Amount: $" << getMaxSpendAmount() << endl;
	return out;
}

string DebitCard::toString() const {
	string info = getCardNumber() + "," + to_string(getSecurityCode()) + "," + getExpireDate().toString() + "," + to_string(getMaxSpendAmount());
	return info;
}