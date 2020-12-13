// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef CREDITCARD_H
#define CREDITCARD_H

#include "Account.h"
#include "Card.h"

class CreditCard : public Card {

	private:
		const double MINIMUM_PAYMENT = 25.00;
		const double APR = 0.16;
		double maxAmount;
		double balanceDue;
		double avaliableBalance;
		Date billDate;
		Date openDate;

		void generateBill();
	public:
		CreditCard(double = 500.0, const Date& = Date::getTodayDate(), const string& = "N/A"); // Starting Limit | Open Date | Name
		CreditCard(const string&, CardType, double, double, double, const Date&, const Date&); // Used to read data from file

		CreditCard& setMaxAmount(double);
		CreditCard& setBalanceDue(double);
		CreditCard& setAvaliableBalance(double);
		CreditCard& setBillDueDate(const Date&);
		CreditCard& setOpenDate(const Date&);

		double getMaxAmount() const;
		double getAvaliableBalance() const;
		double getBalanceDue() const;
		double getMinimumPayment() const;
		double getAPR() const;
		Date getBillDueDate() const;
		Date getOpenedDate() const;

		double makePayment(double, Account*);
		bool transact(double);

		virtual ostream& printInfo(ostream&) const;
		virtual string toString() const;


};


#endif