// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include <iomanip>
#include "User.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "CustomError.h"
#include "CDAccount.h"
#include "RetireAccount.h"
#include "CreditCard.h"
#include "Loans.h"
using namespace std;

template <typename T> 
T getInput(T selection) {
	cin >> selection;
	while (cin.fail()) {
		cout << "\t\t\t (!) Error: You entered bad data. Try again:" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> selection;
	}
	return selection;
}

void displayLoggedMenu(User&);

int main() {
	int selection = -1;
	long userInput = -1;
	string stringInput, stringInput2;
	Date dateInput;

	do {
		cout << endl;
		cout << "\t\t\t\t====== NEW CITY BANK ====== " << endl;
		cout << "\t\t\tWelcome to New City Bank! Please make a selection:" << endl;
		cout << "\t\t\t1.) Login to an existing account" << endl;
		cout << "\t\t\t2.) Create a new account with us" << endl;
		cout << "\t\t\t3.) Exit" << endl;

		selection = getInput(selection);
		cin.ignore();

		if (selection == 1) {
			cout << "\t\t\t>>> Please enter your User ID Number: " << endl;
			userInput = getInput(userInput);
			cin.ignore();

			cout << "\t\t\t>>> Please enter your password: " << endl;
			getline(cin, stringInput);

			User existing(userInput, stringInput);
			try {
				existing.load();
			} catch (const CustomError& err) {
				cerr << err.what() << endl;
			}

			if (existing.isLoggedIn())
				displayLoggedMenu(existing); // This is pass by reference so main is not messy! Making it a separate function appears neater
		} else if (selection == 2) {
			cout << "\t\t\t>>> Please enter your Full Name: " << endl;
			getline(cin, stringInput);

			cout << "\t\t\t>>> Please enter your Date of Birth: (MM/DD/YYYY)" << endl;
			cin >> dateInput;
			cin.ignore();

			cout << "\t\t\t>>> Please set a Password for your Account: " << endl;
			getline(cin, stringInput2);

			User customer(stringInput, dateInput, Date::getTodayDate());
			customer.setPassword(stringInput2);

			cin >> customer;

			cout << "\t\t\tSuccessfully Created Your Account! Here are your details: " << endl;
			cout << "\t\t\t(!) User ID: " << customer.getID() << " | Password: " << customer.getPassword() << " (!) " << endl;
			cout << "\t\t\tLogging out! Please relogin to begin making transactions!" << endl << endl;
		} else if (selection == 3) {
			cout << "\t\t\tThank you for using New City Bank! Have a great day!" << endl;
		} else {
			cout << "\t\t\t>>> ERROR: Invalid Selection! Try agin" << endl;
		}
	} while (selection != 3);

	return 0;

}

void displayLoggedMenu(User& user) {
	int selection = -1, userInput = -1, userInput2 = -1, userInput3 = -1;
	double moneySelection = -1.0;
	char selectionChar = 0;
	long IDs = -1, IDs2 = -1;
	string stringInput;
	Date dateInput;
	do {
		cout << endl;
		cout << "\t\t\t\tWelcome " << user.getFullName() << endl;
		cout << "\t\t\t--------------------------------------" << endl;
		cout << "\t\t\tWhat would you like to do today?" << endl;
		cout << "\t\t\t1) Print Account Information" << endl;
		cout << "\t\t\t2) Modify My Accounts" << endl;  
		cout << "\t\t\t3) Open an Account" << endl; 
		cout << "\t\t\t4) Make a Credit Card Payment" << endl;
		cout << "\t\t\t5) Make a Loan Payment" << endl; 
		cout << "\t\t\t6) Apply for a Credit Card" << endl; 
		cout << "\t\t\t7) Apply for a Loan" << endl; 
		cout << "\t\t\t8) List all Closed Accounts" << endl; 
		cout << "\t\t\t9) Make a Credit Card Transaction" << endl;
		cout << "\t\t\t10) Logout" << endl;
		selection = getInput(selection);
		cin.ignore();

		if (selection == 1) {
			cout << user << endl;
		} else if (selection == 2) {
			if (user.getOpenAccounts().empty()) {
				cout << "\t\t\t(!) Error: You do not have any open accounts!" << endl;
			} else {
				user.printOpenAccounts();

				cout << "\t\t\t >>> Enter the Account Number to Modify:" << endl;
				IDs = getInput(IDs);

				Account* acc = user.getAccountByID(IDs);
				while (acc == nullptr && IDs != -1) {
					cout << "\t\t\t(!) Error: Account with that ID was not found!" << endl;
					cout << "\t\t\t>>> Please enter the Account ID or -1 to return" << endl;
					IDs = getInput(IDs);
					acc = user.getAccountByID(IDs);
				}

				if (acc != nullptr) {
					cout << "\t\t\tSelect the Following Modifications:" << endl;
					cout << "\t\t\t--------------------------------------" << endl;
					cout << "\t\t\t1) Withdraw Money" << endl;
					cout << "\t\t\t2) Deposit Money" << endl;
					cout << "\t\t\t3) Transfer Balance" << endl;
					cout << "\t\t\t4) Close the Account" << endl;
					cout << "\t\t\t5) Return to Main Menu" << endl;
					selection = getInput(selection);

					switch (selection) {
					case 1:
						cout << "\t\t\t>>> Please Enter Amount to Withdraw:" << endl;
						moneySelection = getInput(moneySelection);
						try {
							double actual = acc->withdraw(moneySelection);
							cout << fixed << setprecision(2) << "\t\t\tYou have successfully withdrew $" << actual << endl;
						} catch (const CustomError& err) {
							cerr << err.what() << endl;
						}
						break;
					case 2:
						cout << "\t\t\t>>> Please enter the amount you wish to deposit:" << endl;
						moneySelection = getInput(moneySelection);
						try {
							double actual = acc->deposit(moneySelection);
							cout << fixed << setprecision(2) << "\t\t\tYou have successfully deposited $" << actual << endl;
						} catch (const CustomError& err) {
							cerr << err.what() << endl;
						}
						break;
					case 3:
					{
						cout << "\t\t\t>>> Please enter the amount you wish to transfer: " << endl;
						moneySelection = getInput(moneySelection);


						cout << "\t\t\t>>> Please enter the Account Number to transfer money TO:" << endl;
						IDs2 = getInput(IDs2);
						Account* transferTo = user.getAccountByID(IDs2);
						while (transferTo == nullptr && IDs2 != -1) {
							cout << "\t\t\t(!) Error: Account with that ID was not found!" << endl;
							cout << "\t\t\t>>> Please enter the Account ID or -1 to return" << endl;
							IDs2 = getInput(IDs2);
							transferTo = user.getAccountByID(IDs2);
						}

						if (transferTo != nullptr) {
							try {
								double actual = acc->transfer(transferTo, moneySelection);
								cout << fixed << setprecision(2) << "\t\t\tSuccessfully transfered $" << actual << " over!" << endl;
							} catch (const CustomError& err) {
								cerr << err.what() << endl;
							}
						}
					}
					break;
					case 4:
						cout << "\t\t\t>>> Are you sure you want to close this account?" << endl;
						cout << "\t\t\t>>> Enter 'Y' for Yes and any character for No" << endl;
						selectionChar = getInput(selectionChar);
						if (selectionChar == 'Y' || selectionChar == 'y') {
							if (user.closeAccount(acc)) {
								cout << "\t\t\tSuccessfully Closed Account # " << IDs << endl;
							}
						}
						break;
					case 5:
						cout << "Going back to Main Menu..." << endl;
						break;
					default:
						cout << "\t\t\t(!) Error: You made an invalid selection" << endl;
						break;
					}
				}
			}
		} else if (selection == 3) {
			user.printAllAccountInfo();
			cout << "\n5) Cancel and Go Back" << endl;
			cout << "\t\t\t>>> Please enter 1 - 4 of the Account you wish to open:" << endl;
			selection = getInput(selection);
			while (selection < 1 || selection > 5) {
				cout << "\t\t\t(!) Error: Please enter a value between 1 and 5:" << endl;
				selection = getInput(selection);
			}

			switch (selection) {
				case 1: 
				{
					CheckingAccount* acc = new CheckingAccount(user.getFullName());
					acc->setMonthlyCharge(user.getCreatedDate());
					cin >> *acc;
					cout << "----- < NEW ACCOUNT INFO > -----" << endl << *acc << endl;
					if (user.addAccount(acc)) {
						cout << "\t\t\tCongratulations! You just successfully opened a Checking Account!" << endl;
					} else {
						cout << "\t\t\t(!) Error: An unexpected error has occured! Try again later" << endl;
					}
				}
					break;
				case 2:
				{
					CDAccount* acc = new CDAccount(user.getFullName());
					cin >> *acc;
					cout << "----- < NEW ACCOUNT INFO > -----" << endl << *acc << endl;
					if (user.addAccount(acc)) {
						cout << "\t\t\tCongratulations! You just successfully opened a CD Account!" << endl;
					} else {
						cout << "\t\t\t(!) Error: An unexpected error has occured! Try again later" << endl;
					}
				}
					break;
				case 3:
				{
					RetireAccount* acc = new RetireAccount(user.getFullName());
					cin >> *acc;
					cout << "----- < NEW ACCOUNT INFO > -----" << endl << *acc << endl;
					if (user.addAccount(acc)) {
						cout << "\t\t\tCongratulations! You just successfully opened a Retirement Account!" << endl;
					} else {
						cout << "\t\t\t(!) Error: An unexpected error has occured! Try again later" << endl;
					}
				}
					break;
				case 4:
				{
					SavingsAccount* acc = new SavingsAccount(user.getFullName());
					cin >> *acc;
					cout << "----- < NEW ACCOUNT INFO > -----" << endl << *acc << endl;
					if (user.addAccount(acc)) {
						cout << "\t\t\tCongratulations! You just successfully opened a Savings Account!" << endl;
					}
					else {
						cout << "\t\t\t(!) Error: An unexpected error has occured! Try again later" << endl;
					}
				}
					break;
				case 5:
					cout << "Going back to main menu....." << endl;
					break;
				default:
					cout << "\t\t\t(!) Error: You made an invalid selection" << endl;
					break;
			}

		} else if (selection == 4) {
			if (user.getCreditCards().empty()) {
				cout << "\t\t\t(!) Error: You do not have any open Credit Cards!" << endl;
			} else {
				user.printOpenAccounts();
				user.printCreditCards();

				cout << "\t\t\t>>> Please enter the Credit Card ID #:" << endl;
				userInput = getInput(userInput);

				cout << "\t\t\t>>> Please enter the Account Number to Pay with:" << endl;
				IDs = getInput(IDs);
				Account* acc = user.getAccountByID(IDs);
				while (acc == nullptr && IDs != -1) {
					cout << "\t\t\t(!) Error: Account with that ID was not found!" << endl;
					cout << "\t\t\t>>> Please enter the Account ID or -1 to return" << endl;
					IDs = getInput(IDs);
					acc = user.getAccountByID(IDs);
				}

				if (acc != nullptr) {
					cout << "\t\t\t>>> Please Enter the Payment Amount:" << endl;
					moneySelection = getInput(moneySelection);

					try {
						double amount = user.getCreditCards().at(userInput - 1)->makePayment(moneySelection, acc);
						cout << fixed << setprecision(2) << "\t\t\tSuccessfully Posted a Payment of: $" << amount << endl;
					} catch (const CustomError& err) {
						cerr << err.what() << endl;
					} catch (const out_of_range& error) {
						cerr << "\t\t\t(!) Error: You entered an Invalid Credit Card #" << endl;
					}
				}
			}
		} else if (selection == 5) {
			if (user.getLoans().empty()) {
				cout << "\t\t\t(!) Error: You do not have any Loans!" << endl;
			} else {
				user.printOpenAccounts();
				user.printLoans();

				cout << "\t\t\t>>> Please enter the Loan ID #:" << endl;
				userInput = getInput(userInput);

				cout << "\t\t\t>>> Please enter the Account Number to Pay with:" << endl;
				IDs = getInput(IDs);
				Account* acc = user.getAccountByID(IDs);
				while (acc == nullptr && IDs != -1) {
					cout << "\t\t\t(!) Error: Account with that ID was not found!" << endl;
					cout << "\t\t\t>>> Please enter the Account ID or -1 to return" << endl;
					cin >> IDs;
					acc = user.getAccountByID(IDs);
				}

				if (acc != nullptr) {
					cout << "\t\t\t>>> Please Enter the Payment Amount:" << endl;
					moneySelection = getInput(moneySelection);

					try {
						double amount = user.getLoans().at(userInput - 1)->makePayment(moneySelection, acc);
						cout << fixed << setprecision(2) << "\t\t\tSuccessfully Posted a Payment of: $" << amount << endl;
					} catch (const CustomError& err) {
						cerr << err.what() << endl;
					} catch (const out_of_range& error) {
						cerr << "\t\t\t(!) Error: You entered an Invalid Loan ID #" << endl;
					}
				}
			}
		} else if (selection == 6) {
			user.printCreditCardInfo();

			cout << "\t\t\t>>> Please enter your credit score:" << endl;
			userInput = getInput(userInput);
			while (userInput <= 0) {
				cout << "\t\t\t(!) Error: Please enter a number greater than 0" << endl;
				userInput = getInput(userInput);		
			}
			try {
				double amount = user.openCreditCard(userInput);
				if (amount != 0) {
					cout << "\t\t\tCongratulations! You were approved for a maximum amount of $" << amount << endl;
				} else {
					cout << "\t\t\tSorry! Your credit score is not high enough for a credit card!" << endl;
				}
			} catch (const CustomError& err) {
				cerr << endl << err.what() << endl;
			}

		} else if (selection == 7) {
			user.printLoanInfo();

			cout << "\t\t\t>>> Select the Type of Loan: " << endl;
			userInput = getInput(userInput);
			while (userInput < 1 || userInput > 3) {
				cout << "\t\t\t(!) Error: Invalid selection. Try again" << endl;
				userInput = getInput(userInput);
			}

			cout << "\t\t\t>>> Please enter your Credit Score: " << endl;
			userInput2 = getInput(userInput2);
			while (userInput2 <= 0) {
				cout << "\t\t\t(!) Error: Please enter a number greater than 0" << endl;
				userInput2 = getInput(userInput2);
			}

			cout << "\t\t\t>>> Please enter the Term in Years: " << endl;
			userInput3 = getInput(userInput3);
			while (userInput3 <= 0) {
				cout << "\t\t\t(!) Error: Please enter a number greater than 0" << endl;
				userInput3 = getInput(userInput3);
			}

			cout << "\t\t\t>>> Please enter the Loan Amount: " << endl;
			moneySelection = getInput(moneySelection);
			while (moneySelection <= 0) {
				cout << "\t\t\t(!) Error: Please enter a value greater than 0" << endl;
				moneySelection = getInput(moneySelection);
			}

			Loans* loan = new Loans(userInput3, moneySelection, Loans::parse(userInput));
			if (!loan->checkAmount(userInput2)) {
				cout << "\t\t\tUnfortunety, your credit score is too low for such a high loan!" << endl;
				cout << "\t\t\tRESULT: Loan Denied" << endl;
				delete loan;
			} else {
				cout << "\t\t\tCongratulations, you have been pre-approved! Here are the details of your Loan: " << endl;
				cout << *loan << endl;
				cout << "\t\t\t>>> Please enter Y to Accept this Loan or a random key to Decline" << endl;
				selectionChar = getInput(selectionChar);
				if (selectionChar == 'Y' || selectionChar == 'y') {
					user.addLoan(loan);
					cout << "\t\t\tCongratulations, your loan has been approved and set!" << endl;
				} else {
					cout << "\t\t\tYou have declined the loan agreement!" << endl;
					delete loan;
				}
			}

		} else if (selection == 8) {
			user.printClosedAccounts();
		} else if (selection == 9) {
			if (user.getCreditCards().empty()) {
				cout << "\t\t\t(!) Error: You do not have any open Credit Cards!" << endl;
			} else {
				user.printCreditCards();

				cout << "\t\t\t>>> Please enter Credit Card Number: " << endl;
				getline(cin, stringInput);
				while (stringInput.length() < 16) {
					cout << "\t\t\t(!) Error: Please enter a valid 16 digit credit card number: " << endl;
					getline(cin, stringInput);
				}

				cout << "\t\t\t>>> Please enter the 3-Digit Security Code (CVC): " << endl;
				userInput = getInput(userInput);
				while ((int)(log10(userInput) + 1) != 3) {
					cout << "\t\t\t(!) Error: Please enter a 3-Digit CVC " << endl;
					userInput = getInput(userInput);
				}

				cout << "\t\t\t>>> Please enter the Expiration Date of the card: (MM/DD/YYYY)" << endl;
				cin >> dateInput;

				CreditCard* card = user.getCreditCard(stringInput, userInput, dateInput);
				if (card == nullptr) {
					cout << "\t\t\t(!) Error: The information you entered did not match any of your credit-card records!" << endl;
				} else {
					cout << "\t\t\t>>> Please enter the Transaction Amount: " << endl;
					moneySelection = getInput(moneySelection);
					while (moneySelection <= 0) {
						cout << "\t\t\t(!) Error: Please enter a value greater than $0.00" << endl;
						moneySelection = getInput(moneySelection);
					}

					if (card->transact(moneySelection)) {
						cout << "\t\t\tSuccessfully made a purchase on CreditCard for $" << moneySelection << endl;
					} else {
						cout << "\t\t\t(!) Your credit card has been declined due to insufficient funds!" << endl;
					}
				}
			}
		} else if (selection == 10) {
			cout << "\t\t\tLogging Out...." << endl;
		} else {
			cout << "\t\t\t>>> (!) Error: Invalid Selection. Try again" << endl;
		}
	} while (selection != 10);

}