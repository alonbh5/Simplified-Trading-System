#ifndef __ADDRESS_H
#define __ADDRESS_H

#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Address
{
public:
	static const int MAX_STR_LENGTH = 31;
	friend class Seller;
	friend class Buyer;
	friend class User;

private:
	string Street;
	string City;
	string Country;
	int houseNumber;
	int Zipcode;
	Address() = default; //just for user ctor

public://Class Public Methods
	//C'tor
	Address(const string& street, const int houseNumber, const string& city, const string& country, const int zipcode);
	Address(const Address& other) = default;

	//Operators
	friend ostream& operator<<(ostream& os, const Address& obj);
	friend istream& operator>>(istream& in, Address& obj);

private://Class Private Methods
	bool setStreet(const string& street);
	bool setCity(const string& city);
	bool setNumber(const int houseNumber);
	bool setZipcode(const int Zipcode);
	bool setCountry(const string& Country);
	void getStrFromFile(istream& in, string& str, int len); // Helper for loading file


public://Class Public Methods
	const string& getStreet() const;
	const string& getCity()   const;
	const string& getCountry()   const;
	int getNumber()         const;
	int getZipcode()         const;
	void show() const;
};
#endif // __ADDRESS_H