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
		char Street[MAX_STR_LENGTH];
		char City[MAX_STR_LENGTH];
		char Country[MAX_STR_LENGTH];
		int houseNumber;
		int Zipcode;

	public://Class Public Methods
		//C'tor
		Address(const char* street, const int houseNumber, const char* city, const char* country, const int zipcode); 
		Address(const Address& other) = default; 
		//Operators
		const Address& operator=(const Address& other);
		const Address& operator=(const Address&& other);
		friend ostream& operator<<(ostream& os, const Address& obj);

	private://Class Private Methods
		bool setStreet(const char* street);
		bool setCity(const char* city);
		bool setNumber(const int houseNumber);
		bool setZipcode(const int Zipcode);
		bool setCountry(const char* Country);

	public://Class Public Methods
		const char* getStreet() const;
		const char* getCity()   const;
		const char* getCountry()   const;
		int getNumber()         const;
		int getZipcode()         const;
		void show() const;
};
#endif // __ADDRESS_H