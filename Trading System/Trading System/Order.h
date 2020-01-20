#ifndef _ORDER_H
#define _ORDER_H

#pragma warning(disable : 4996)
using namespace std;
#include <iostream>
#include <string>
#include"Buyer.h"
#include "Product.h"
#include <vector>

class Buyer;
class Product;

class Order 
{
public:
	static const int ALLOCATION_ERROR = -1;
	friend class System;

private: ////Class Variables 
	static int OrderCounter;
	double Totalprice;
	int const OrderSerialNumber;
	const Buyer& buyer;
	vector<Product*> order_list;
	bool Payed;

private: //Class Helper Vatiables
	//int Physize_orderlist;
	//int Logsize_orderlist;

public: //Constractur, Move, Destractor
	Order(const Buyer& buyer); //reset with buyer
	Order(const Order &other) = delete;
	Order(Order &&other);
	~Order();
	
	//GETS
	double getprice() const;
	const Buyer& getbuyer() const;
	int getOrderSerialNumber() const;
	int getPhysize_orderlist() const;
	int getLogsize_orderlist() const;
	bool getPayed() const;
	
	//SETS
	//bool setOrderlist();

	//OTHER
	bool AddProducttolist(Product* prod_to_add);
	bool Payment();
	void print() const;
	bool IsAllAvailable() const;
	//bool RemovePrudFromOrder(Product* prod_to_del);
	void ClearNotAvailable();
	bool DidBuyerBuyFromSeller(const Seller* seller) const;

private: //PRIVATE METHODS
	bool setprice(double price); 
	bool calculateprice();
	bool setPayed();
//	void HelperForCallocOrderList();
	bool removeFromOrderList(Product* prod_to_del);
	vector<Product*> getorderlist() const;

	
};

#endif // !_ORDER_H