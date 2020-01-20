#ifndef _SELLER_H
#define _SELLER_H

#pragma warning(disable : 4996)

#include <iostream>
#include <string.h>
#include "User.h"
#include "Product.h"
#include "Address.h"
#include "Feedback.h"
#include <vector>

using namespace std;
class Product;
class Feedback; 

class Seller: virtual public User
{
public:
	static const int ALLOCATION_ERROR = -1;
	friend class System;

	//Class variables
protected:
	vector<Product*> p_list;
	vector<Feedback*> f_list;

public://Constractur, Move, Destractor
	Seller(const char* name, const char* password, const Address& OfficeAddress);
	Seller(Seller&& other);
	virtual ~Seller();

protected: //Class Protected Methods
	vector<Feedback*> getAllFeedbacks() const;
	vector<Product*> getAllProducts() const;
	Product* findCertainProductInList(const int sir_num) const;

public: //Class Public Methods
	friend ostream& operator<<(ostream& os, const Seller& obj);
	const Seller& operator=(Seller&& other);
	virtual void save(ofstream& out_file);
	

	//OTHERS
	bool addNewProductforList(Product* p_data);
	bool addNewFeedbackforList(Feedback* f_data);
	int AmountOfProductList() const;
	int AmountOfFeedback() const;
	void printProductList() const;
	void printFeedbackList() const;
	virtual void show() const override;
};
#endif //_SELLER_H