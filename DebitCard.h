// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef DEBITCARD_H
#define DEBITCARD_H

#include "Card.h"
#include "CardType.h"
using namespace std;

class DebitCard : public Card {
	private:
		double maxSpendAmount;
	public:
		DebitCard(const string & = "N/A", CardType = CardType::DEBIT, double = 1000.0); // Name | Debit Card | Max Spend Amount
		DebitCard(const string&, CardType, double, bool); // Used for reading data  from file

		DebitCard& setMaxSpendAmount(double);
		double getMaxSpendAmount() const;

		virtual ostream& printInfo(ostream&) const;
		virtual string toString() const;
};


#endif