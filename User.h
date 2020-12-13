// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef USER_H
#define USER_H

#include "CreditCard.h"
#include "Loans.h"
using namespace std;

class User {

	friend ostream& operator<<(ostream&, const User&);
	friend istream& operator>>(istream&, User&);

	private:
		static vector<long> IDs;

		long ID;
		string password;
		bool loggedIn;

		string fullName;
		string streetAddress;
		string city;
		string state;
		string zipCode;
		string socialSecurity;
		string phoneNumber;
		Date birthday;
		Date createdDate;
		vector<Account*> openAccounts;
		vector<Account*> closedAccounts;
		vector<CreditCard*> creditCards;
		vector<Loans*> loans;

		bool contains(long);
		void setID();
		void save();
	public:
		User(long, const string&); // Take in user ID and parse information from file
		User(const string&, const Date&, const Date&); // Full name, Birthday, Create Date
		~User();

		void load();

		long getID() const;
		string getPassword() const;
		string getFullName() const;
		string getStreetAddress() const;
		string getCity() const;
		string getState() const;
		string getZipCode() const;
		string getSSN() const;
		string getPhoneNumber() const;
		Date getBirthday() const;
		Date getCreatedDate() const;
		const vector<Account*>& getOpenAccounts() const;
		const vector<Account*>& getClosedAccounts() const;
		const vector<CreditCard*>& getCreditCards() const;
		const vector<Loans*>& getLoans() const;
		int getAge() const;
		bool isLoggedIn() const;
		string toString() const;

		User& setPassword(const string&);
		User& setFullName(const string&);
		User& setStreetAddress(const string&);
		User& setCity(const string&);
		User& setState(const string&);
		User& setZipCode(const string&);
		User& setSSN(const string&);
		User& setPhoneNumber(const string&);
		User& setBirthdate(const Date&);
		User& setOpenDate(const Date&);

		Account* getAccountByID(long) const;
		CreditCard* getCreditCard(const string&, int, const Date&);
		double openCreditCard(int);

		bool addAccount(Account*);
		bool closeAccount(Account*);
		bool addCreditCard(CreditCard*);
		bool cancelCreditCard(CreditCard*);
		bool addLoan(Loans*);

		void printOpenAccounts() const;
		void printClosedAccounts() const;
		void printCreditCards() const;
		void printLoans() const;

		void printAllAccountInfo() const;
		void printCreditCardInfo() const;
		void printLoanInfo() const;
};

#endif