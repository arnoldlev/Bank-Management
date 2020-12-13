// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef CUSTOMERROR_H
#define CUSTOMERROR_H

#include <stdexcept>
#include <string>
using namespace std;

class CustomError : public runtime_error {
	public:
		CustomError(const string& s):runtime_error("\t\t\t(!) " + s) {
		}
};

#endif