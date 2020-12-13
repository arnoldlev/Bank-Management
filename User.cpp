// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "User.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "CDAccount.h"
#include "RetireAccount.h"
#include "CustomError.h"
#include <fstream>
#include <sstream>
using namespace std;

vector<long> User::IDs;

User::User(long ID, const string& password) {
	this->ID = ID;
	setPassword(password);
	loggedIn = false;
}

User::User(const string& name, const Date& birth, const Date& created) { 
	setID();
	setFullName(name).setBirthdate(birth).setOpenDate(created);
	loggedIn = true;
}

User::~User() {
	if (isLoggedIn()) {
		save();
	}

	for (int i = 0; i < (int) openAccounts.size(); i++) {
		delete openAccounts[i];
	}

	for (int i = 0; i < (int) closedAccounts.size(); i++) {
		delete closedAccounts[i];
	}

	for (int i = 0; i < (int) creditCards.size(); i++) {
		delete creditCards[i];
	}

	for (int i = 0; i < (int)loans.size(); i++) {
		delete loans[i];
	}
}

void User::setID() {
	ID = 0;
	srand((unsigned int)time(NULL));
	for (int i = 1; i <= 10; i++) {
		ID += rand() % 350000 + 215000;
	}

	while (contains(ID)) {
		for (int i = 1; i <= 10; i++) {
			ID += rand() % 350000 + 215000;
		}
	}
	IDs.push_back(ID);
}

bool User::contains(long num) {
	for (int i = 0; i < (int) IDs.size(); i++) {
		if (IDs[i] == num) {
			return true;
		}
	}
	return false;
}

void User::load() {
	string file = to_string(ID) + ".txt";
	vector<string> data;
	string holder, line;
	ifstream read(file, ios::in);

	if (read.fail()) {
		throw CustomError("Error: User ID not found! Try again");
	} else {
		getline(read, line);
		stringstream msg(line);
		while (getline(msg, holder, ',')) {
			data.push_back(holder);
		}

		if (data[9] != getPassword()) {
			read.close();
			throw CustomError("Error: Incorrect Password!");
		} else {
			Date bday(data[7]);
			Date created(data[8]);
			setFullName(data[0]).setStreetAddress(data[1]).setCity(data[2]).setState(data[3]).setZipCode(data[4]);
			setSSN(data[5]).setPhoneNumber(data[6]).setBirthdate(bday).setOpenDate(created);

			IDs.push_back(ID);
		}
	}
	read.close();
	data.clear();
	line = "", holder = "";

	file = to_string(ID) + "Accounts.txt";
	read.open(file, ios::in);
	if (!read.fail()) {
		getline(read, line);
		while (!read.fail()) {
			stringstream msg(line);
			while (getline(msg, holder, ',')) {
				data.push_back(holder);
			}

			if (!data.empty()) {
				string type = data[0];
				if (type == "CheckingAccount") {
					Date open(data[4]);
					Date close(data[5]);
					Date expire(data[10]);
					CheckingAccount* acc = new CheckingAccount(data[1], stol(data[2]), stod(data[3]), open, close, stod(data[6]), stod(data[7]), stod(data[11]));
					acc->setDebitCard(data[8], stoi(data[9]), expire);
					addAccount(acc);
				} else if (type == "SavingsAccount") {
					Date open(data[4]);
					Date close(data[5]);
					SavingsAccount* acc = new SavingsAccount(data[1], stol(data[2]), stod(data[3]), open, close, stod(data[6]));
					addAccount(acc);
				} else if (type == "CDAccount") {
					Date open(data[4]);
					Date close(data[5]);
					Date mature(data[6]);
					CDAccount* acc = new CDAccount(data[1], stol(data[2]), stod(data[3]), open, close, stod(data[7]), stod(data[8]), mature);
					addAccount(acc);
				} else if (type == "RetireAccount") {
					Date open(data[4]);
					Date close(data[5]);
					Date retire(data[6]);
					RetireAccount* acc = new RetireAccount(data[1], stol(data[2]), stod(data[3]), open, close, retire, stod(data[7]));
					addAccount(acc);
				}
			}
			getline(read, line);
			data.clear();
		}
	}
	read.close();
	data.clear();
	line = "", holder = "";

	file = to_string(ID) + "ClosedAccounts.txt";
	read.open(file, ios::in);
	if (!read.fail()) {
		getline(read, line);

		while (!read.fail()) {
			stringstream msg(line);
			while (getline(msg, holder, ',')) {
				data.push_back(holder);
			}

			if (!data.empty()) {
				string type = data[0];
				if (type == "CheckingAccount") {
					Date open(data[4]);
					Date close(data[5]);
					Date expire(data[10]);
					CheckingAccount* acc = new CheckingAccount(data[1], stol(data[2]), stod(data[3]), open, close, stod(data[6]), stod(data[7]), stod(data[11]));
					acc->setDebitCard(data[8], stoi(data[9]), expire);
					closedAccounts.push_back(acc);
				} else if (type == "SavingsAccount") {
					Date open(data[4]);
					Date close(data[5]);
					SavingsAccount* acc = new SavingsAccount(data[1], stol(data[2]), stod(data[3]), open, close, stod(data[6]));
					closedAccounts.push_back(acc);
				} else if (type == "CDAccount") {
					Date open(data[4]);
					Date close(data[5]);
					Date mature(data[6]);
					CDAccount* acc = new CDAccount(data[1], stol(data[2]), stod(data[3]), open, close, stod(data[7]), stod(data[8]), mature);
					closedAccounts.push_back(acc);
				} else if (type == "RetireAccount") {
					Date open(data[4]);
					Date close(data[5]);
					Date retire(data[6]);
					RetireAccount* acc = new RetireAccount(data[1], stol(data[2]), stod(data[3]), open, close, retire, stod(data[7]));
					closedAccounts.push_back(acc);
				}
			}
			getline(read, line);
			data.clear();

		}
	}
	read.close();
	data.clear();
	line = "", holder = "";

	file = to_string(ID) + "CreditCards.txt";
	read.open(file, ios::in);
	if (!read.fail()) {
		getline(read, line);

		while (!read.fail()) {
			stringstream msg(line);
			while (getline(msg, holder, ',')) {
				data.push_back(holder);
			}

			if (!data.empty()) {
				Date expire(data[3]);
				Date open(data[7]);
				Date close(data[8]);
				CreditCard* credit = new CreditCard(data[0], CardType::CREDIT, stod(data[4]), stod(data[5]), stod(data[6]), open, close);
				credit->setName(data[0]).setCardNumber(data[1]).setCVC(stoi(data[2])).setExpireDate(expire);
				addCreditCard(credit);
			}
			getline(read, line);
			data.clear();
		}
	}
	read.close();
	data.clear();
	line = "", holder = "";

	file = to_string(ID) + "Loans.txt";
	read.open(file, ios::in);
	if (!read.fail()) {
		getline(read, line);

		while (!read.fail()) {
			stringstream msg(line);
			while (getline(msg, holder, ',')) {
				data.push_back(holder);
			}

			if (!data.empty()) {
				Date open(data[7]);
				Date bill(data[6]);
				LoanType type = Loans::parse(data[5]);
				Loans* loan = new Loans(stod(data[0]), stod(data[1]), stod(data[2]), stod(data[3]), stoi(data[4]), type, bill, open);
				addLoan(loan);
			}
			getline(read, line);
			data.clear();
		}
	}

	read.close();
	data.clear();
	loggedIn = true;
}

void User::save() {
	string file = to_string(ID) + ".txt";
	ofstream write(file, ios::out);

	write << toString() << endl;
	write.close();

	if (openAccounts.size() >= 1) {
		file = to_string(ID) + "Accounts.txt";
		write.open(file, ios::out);
		for (int i = 0; i < (int)openAccounts.size(); i++) {
			write << openAccounts[i]->toString() << endl;
		}
		write.close();
	}

	if (closedAccounts.size() >= 1) {
		file = to_string(ID) + "ClosedAccounts.txt";
		write.open(file, ios::out);
		for (int i = 0; i < (int)closedAccounts.size(); i++) {
			write << closedAccounts[i]->toString() << endl;
		}
		write.close();
	}

	if (creditCards.size() >= 1) {
		file = to_string(ID) + "CreditCards.txt";
		write.open(file, ios::out);
		for (int i = 0; i < (int)creditCards.size(); i++) {
			write << creditCards[i]->toString() << endl;
		}
		write.close();
	}

	if (loans.size() >= 1) {
		file = to_string(ID) + "Loans.txt";
		write.open(file, ios::out);
		for (int i = 0; i < (int)loans.size(); i++) {
			write << loans[i]->toString() << endl;
		}
		write.close();
	}
}

User& User::setFullName(const string& name) {
	if (name.length() > 1) {
		fullName = name;
	} else {
		fullName = "N/A";
	}
	return *this;
}

User& User::setStreetAddress(const string& address) {
	if (address.length() > 1) {
		streetAddress = address;
	} else {
		streetAddress = "N/A";
	}
	return *this;
}

User& User::setCity(const string& city) {
	if (city.length() > 1) {
		this->city = city;
	}
	else {
		this->city = "N/A";
	}
	return *this;
}

User& User::setState(const string& state) {
	if (state.length() == 2) {
		this->state = state;
	}
	else {
		this->state = "N/A";
	}
	return *this;
}

User& User::setZipCode(const string& zip) {
	if (zip.length() > 1) {
		zipCode = zip;
	}else {
	 	zipCode = "N/A";
	}
	return *this;
}

User& User::setSSN(const string& ssn) {
	if (ssn.length() == 11) {
		socialSecurity = ssn;
	} else {
		socialSecurity = "N/A";
	}
	return *this;
}

User& User::setPhoneNumber(const string& number) {
	if (number.length() == 12) {
		phoneNumber = number;
	} else {
		phoneNumber = "N/A";
	}
	return *this;
}

User& User::setBirthdate(const Date& date) {
	birthday.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

User& User::setOpenDate(const Date& date) {
	createdDate.setDate(date.getMonth(), date.getDay(), date.getYear());
	return *this;
}

User& User::setPassword(const string& pw) {
	password = pw;
	return *this;
}

long User::getID() const {
	return ID;
}

string User::getFullName() const {
	return fullName;
}

string User::getStreetAddress() const {
	return streetAddress;
}

string User::getCity() const {
	return city;
}

string User::getState() const {
	return state;
}

string User::getZipCode() const {
	return zipCode;
}

string User::getSSN() const {
	return socialSecurity;
}

string User::getPhoneNumber() const {
	return phoneNumber;
}

Date User::getBirthday() const {
	return birthday;
}

Date User::getCreatedDate() const {
	return createdDate;
}

string User::getPassword() const {
	return password;
}

int User::getAge() const {
	int age = Date::getTodayDate().getYear() - birthday.getYear();
	return age;
}

const vector<Account*>& User::getOpenAccounts() const {
	return openAccounts;
}

const vector<Account*>& User::getClosedAccounts() const {
	return closedAccounts;
}

const vector<CreditCard*>& User::getCreditCards() const {
	return creditCards;
}

const vector<Loans*>& User::getLoans() const {
	return loans;
}

bool User::isLoggedIn() const {
	return loggedIn;
}

Account* User::getAccountByID(long accID) const {
	for (int i = 0; i < (int) getOpenAccounts().size(); i++) {
		if (getOpenAccounts()[i]->getAccountNumber() == accID) {
			return getOpenAccounts()[i];
		}
	}
	return nullptr;
}

CreditCard* User::getCreditCard(const string& cardNum, int cvc, const Date& expire) {
	for (int i = 0; i < (int) getCreditCards().size(); i++) {
		CreditCard* card = getCreditCards()[i];
		if (card->getCardNumber() == cardNum && card->getSecurityCode() == cvc && card->getExpireDate() == expire) {
			return card;
		}
	}
	return nullptr;
}

string User::toString() const {
	string parsed = getFullName() + "," + getStreetAddress() + "," + getCity() + "," + getState() + "," + getZipCode() + "," + getSSN()
		+ "," + getPhoneNumber() + "," + getBirthday().toString() + "," + getCreatedDate().toString() + "," + getPassword();
	return parsed;
}

double User::openCreditCard(int score) {
	if (score < 500) {
		return 0;
	} else {
		CreditCard* card = new CreditCard();
		if (score >= 500 && score <= 600) {
			card->setMaxAmount(500).setAvaliableBalance(500).setName(getFullName());
		} else if (score > 600 && score <= 700) {
			card->setMaxAmount(1000).setAvaliableBalance(1000).setName(getFullName());
		} else if (score > 700) {
			card->setMaxAmount(2000).setAvaliableBalance(2000).setName(getFullName());
		}

		if (!addCreditCard(card)) {
			throw CustomError("Error: An error has occured creating creditcard. Try again!");
		}
		return card->getMaxAmount();
	}
}

bool User::addLoan(Loans* loan) {
	loans.push_back(loan);
	return true;
}

bool User::addAccount(Account* acc) {
	for (int i = 0; i < (int) openAccounts.size(); i++) {
		if (*(openAccounts[i]) == *(acc)) {
			return false;
		}
	}
	openAccounts.push_back(acc);
	return true;
}

bool User::closeAccount(Account* acc)  {
	for (int i = 0; i < (int) openAccounts.size(); i++) {
		if (*(openAccounts[i]) == *(acc)) {
			acc->setCloseDate(Date::getTodayDate());
			openAccounts.erase(openAccounts.begin() + i);
			closedAccounts.push_back(acc);
			return true;
		}
	}
	return false;
}

bool User::addCreditCard(CreditCard* card) {
	for (int i = 0; i < (int) creditCards.size(); i++) {
		if (*(creditCards[i]) == *(card)) {
			return false;
		}
	}
	creditCards.push_back(card);
	return true;
}

bool User::cancelCreditCard(CreditCard* card) {
	for (int i = 0; i < (int) creditCards.size(); i++) {
		if (*(creditCards[i]) == *(card)) {
			delete creditCards[i];
			creditCards.erase(creditCards.begin() + i);
			return true;
		}
	}
	return false;
}

void User::printOpenAccounts() const {
	cout << endl << ">----------<  ACCOUNTS INFORMATION >----------<" << endl;
	for (int i = 0; i < (int) getOpenAccounts().size(); i++) {
		cout << *(getOpenAccounts()[i]) << endl;
	}
	cout << endl;
}

void User::printClosedAccounts() const {
	cout << endl << ">----------<  CLOSED INFORMATION >----------<" << endl;
	for (int i = 0; i < (int)getClosedAccounts().size(); i++) {
		cout << *(getClosedAccounts()[i]) << endl;
	}
	cout << endl;
}

void User::printCreditCards() const {
	cout << endl << ">----------<  CREDIT CARDS >----------<" << endl;
	for (int i = 0; i < (int)getCreditCards().size(); i++) {
		cout << "ID #: " << (i + 1) << endl;
		cout <<  *(getCreditCards()[i]) << endl;
	}
	cout << endl;
}

void User::printLoans() const {
	cout << endl << ">----------<  LOANS >----------<" << endl;
	for (int i = 0; i < (int)getLoans().size(); i++) {
		cout << "ID #: " << (i + 1) << endl;
		cout << *(getLoans()[i]) << endl;
	}
	cout << endl;
}

istream& operator>>(istream& in, User& user) {
	cout << "\t\t\t>>> Please enter your street address:" << endl;
	getline(in, user.streetAddress);

	cout << "\t\t\t>>> Please enter your city:" << endl;
	getline(in, user.city);

	cout << "\t\t\t>>> Please enter your two letter state: (EX: CA)" << endl;
	getline(in, user.state);
	while (user.state.length() != 2) {
		cout << "\t\t\t(!) Error: Please enter a valid state: (EX: CA)" << endl;
		getline(in, user.state);
	}

	cout << "\t\t\t>>> Please enter your 5 digit zipcode:" << endl;
	getline(in, user.zipCode);
	while (user.zipCode.length() != 5) {
		cout << "\t\t\t(!) Error: Please enter a valid zipcode: (EX: 91203)" << endl;
		getline(in, user.zipCode);
	}

	cout << "\t\t\t>>> Please enter your social security number: (EX: 555-55-5555)" << endl;
	getline(in, user.socialSecurity);
	while (user.socialSecurity.length() != 11) {
		cout << "\t\t\t(!) Error: Please enter a valid SSN: (EX: 555-55-5555)" << endl;
		getline(in, user.socialSecurity);
	}

	cout << "\t\t\t>>> Please enter your phone number: (EX: 818-555-5555)" << endl;
	getline(in, user.phoneNumber);
	while (user.phoneNumber.length() != 12) {
		cout << "\t\t\t(!) Error: Please enter a valid phone number: (EX: 818-555-5555)" << endl;
		getline(in, user.phoneNumber);
	}

	return in;
}

ostream& operator<<(ostream& out, const User& user) {
	out << user.getFullName() << " Profile: " << endl;
	out << "-----------------------------------------" << endl;
	out << "User ID: " << user.getID() << endl;
	out << "" << user.getStreetAddress() << endl;
	out << user.getCity() << ", " << user.getState() << " " << user.getZipCode() << endl;
	out << "Social Security: " << user.getSSN() << " | Phone Number: " << user.getPhoneNumber() << endl;
	out << "Birthday: " << user.getBirthday() << " (" << user.getAge() << ") | User Since: " << user.getCreatedDate() << endl;

	out << endl << ">----------<  OPEN ACCOUNTS  >----------<" << endl;
	for (int i = 0; i < (int) user.getOpenAccounts().size(); i++) {
		out << *(user.getOpenAccounts()[i]) << endl;
	}

	out << endl << ">----------<  CREDIT CARDS  >----------<" << endl;
	for (int i = 0; i < (int)user.getCreditCards().size(); i++) {
		out << *(user.getCreditCards()[i]) << endl;
	}

	out << endl << ">----------<  LOANS  >----------<" << endl;
	for (int i = 0; i < (int)user.getLoans().size(); i++) {
		out << *(user.getLoans()[i]) << endl;
	}

	return out;

}

void User::printAllAccountInfo() const {
	cout << "1) Checking Accounts" << endl;
	cout << "-----------------" << endl;
	cout << "* Open a Checking Account today with a monthly charge of" << endl;
	cout << "*\tMember Less than 1 Month: $25 | Member More than 1 Month: $15" << endl;
	cout << "* Set your own ATM Limit Withdrawals & Card Limits for security purposes!" << endl;
	cout << "* One Debit Card automatically generated for each Checking Account" << endl;
	cout << endl;
	cout << "2) CD Accounts" << endl;
	cout << "----------------" << endl;
	cout << "* Open a CD Account today to start saving big time!" << endl;
	cout << "* Minimum Deposit of $2,500 Only" << endl;
	cout << "* Interest Rates of 3% if you deposit $2,500 | 5% if you deposit $5,000" << endl;
	cout << "* Set your own term and the minimum amount when to withdraw!" << endl;
	cout << endl;
	cout << "3) Retirement Account" << endl;
	cout << "----------------" << endl;
	cout << "* Open your retirement account now and be rich later" << endl;
	cout << "* Choose your own monthly minimum deposit and retirement date!" << endl;
	cout << endl;
	cout << "4) Savings Account" << endl;
	cout << "----------------" << endl;
	cout << "* Don't want to wait with CDs? Open your savings account now!" << endl;
	cout << "* Interest Rates of 0.02% if starting deposit is $25" << endl;
	cout << "* Interest Rates of 0.05% if starting deposit is $2,500" << endl;
}

void User::printCreditCardInfo() const {
	cout << "Credit Cards at New City Bank" << endl;
	cout << "-----------------------------" << endl;
	cout << "* Minimum Payments: $25 / month" << endl;
	cout << "* APR: 16% " << endl;
	cout << "* Maximum Amount varies from $500 - $2,000" << endl;
	cout << endl;
}

void User::printLoanInfo() const {
	cout << "Loans at New City Bank" << endl;
	cout << "-----------------------------" << endl;
	cout << "1) Personal Loan" << endl;
	cout << "* Score: 500-600 | Up to $10,000" << endl;
	cout << "* Score: 600-700 | Up to $25,000" << endl;
	cout << "* Score: 700-800 | Up to $50,000" << endl;
	cout << "* Score: 800 +   | Up to $100,000" << endl;
	cout << "2) Home Loan" << endl;
	cout << "* Score: 500-600 | Up to $500,000" << endl;
	cout << "* Score: 600-700 | Up to $600,000" << endl;
	cout << "* Score: 700-800 | Up to $900,000" << endl;
	cout << "* Score: 800 +   | Up to $1,500,000" << endl;
	cout << "3) Student Loan" << endl;
	cout << "* No Score Needed! | Up to $70,000" << endl;
	cout << endl;
}