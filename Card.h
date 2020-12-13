// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef CARD_H
#define CARD_H

#include "Date.h"
#include "CardType.h"
#include <vector>
using namespace std;

class Card {

	friend ostream& operator<<(ostream&, const Card&);

	private:
		static vector<string> cardNumbers;

		int cardNumber[16];
		int securityCode;
		string name;
		Date expireDate;
		CardType type;

		void generateCard();
		bool contains(const string&);
		int sum(int[]);
	public:
		Card(const string& = "N/A", CardType = CardType::DEFAULT); // Name | Card Type
		Card(const string&, CardType, double); // Used for reading data from file

		Card& setName(const string&);
		Card& setCardNumber(const string&);
		Card& setCVC(int);
		Card& setExpireDate(const Date&);

		string getName() const;
		string getCardNumber() const;
		int getSecurityCode() const;
		Date getExpireDate() const;
		CardType getType() const;

		bool operator==(const Card&);

		virtual ostream& printInfo(ostream&) const;
		virtual string toString() const = 0;

};


#endif