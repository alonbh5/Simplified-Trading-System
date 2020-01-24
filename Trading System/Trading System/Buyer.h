#ifndef _BUYER_H
#define _BUYER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include "product.h"
#include "Address.h"
#include "Order.h"
#include "Date.h"
#include "Feedback.h"
#include "User.h"

#pragma warning(disable : 4996)
using namespace std;


//Declaration for Classes using in Class Buyer
class Product;
class Address;
class Order;
class Date;
class Feedback;


class Buyer : virtual public User
{
public:
	static const int ALLOCATION_ERROR = -1;
	friend class System;

protected: //Class Variables 
	vector<Product*> Wishlist;
	vector<Order*> order_history;

protected:
	// METHODS THAT ONLY FRIENDS AND INHERITANCE CALSS COULD USED
	vector<Product*> getWishlist() const;
	vector<Order*> getOrderhistory() const;

public: //Class Public Methods
	//Constractur, Move, Destractor 
	Buyer(ifstream& inFile);
	Buyer(const string& name, const string& password, const Address& home_address);
	Buyer(const Buyer& other) = delete;
	virtual ~Buyer();

	//OPERATORS
	friend ostream& operator<<(ostream& os, const Buyer& obj);
	bool operator>(const Buyer& other);
	bool operator<(const Buyer& other);

	//GETS
	int getPhysize_wishlist() const;
	int getLogsize_wishlist() const;
	int getPhysize_history() const;
	int getLogsize_history() const;

	//OTHERS
	bool FindinWIshlist(const Product* FindMe) const;
	bool DidyouBuyfromSeller(const Seller* seller) const;
	bool PrintWishlist() const;
	void printOrder() const;
	int printOrderNotpaid() const;
	virtual void show() const override;
	void showwithpass() const;
	virtual void save(ofstream& out_file);

protected: //Class Protected Methods
	bool AddProductToACertainOrder(Order* order, const int sir);
	void addNewProductforWishList(Product* p_data);
	bool removeProdctfromWislist(Product* p_data);
	void addOrdertoHistory(Order* order);
	void removeLastOrderFromHistory();
	double calculateWishlist() const;
};

#endif // _BUYER_H