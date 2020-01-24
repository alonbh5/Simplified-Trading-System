#ifndef _PRODUCT_H
#define _PRODUCT_H

#pragma warning(disable : 4996)

#include <iostream>
#include <string.h>
#include "Seller.h"
using namespace std;

class Product
{
	//Static class variables
public:
	enum eCategory { KIDS, ELECTRICAL, OFFICE, CLOTHING };
	static constexpr int MAX_LEN_NAME = 21;

	friend class Seller;
	friend class System;

private:
	static int		conterSerial;

	//Class variables
private:
	string			name;
	eCategory		category;
	double			price;
	int const		serialnumber;
	bool			available; //ctor TRUE defult
	const			Seller& seller;// Holding the address of the seller
	const			Buyer* buyer; //Holding the address of the buyer, defult=null

//METHODS
public: //Constractur, Move, Copy, Destractor
	Product(const string& name, const int category, const Seller& seller, const double price = 1);
	Product(const Product& other);
	~Product();

private://Class Private Methods
	//SETERS
	bool setName(const string& name);
	bool setPrice(const double price);
	bool setCategory(const int category);
	void setAvailable(const bool flag);
	void setBuyer(const Buyer* buyer = nullptr);

public: //Class Public Methods
	//GETERS
	const string& getName() const;
	const Seller& getSeller() const;
	int getCategory() const;
	double getPrice() const;
	int getSerialNumber() const;
	bool getAvailable() const;
	int getHowManyProductsInSystem() const;

	//OTHERS
	void print() const;
	friend ostream& operator<<(ostream& os, const Product& prod);
};

#endif // _PRODUCT_H