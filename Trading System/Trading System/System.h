#ifndef _SYSTEM_H
#define _SYSTEM_H
#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string.h>
#include <typeinfo>
#include "User.h"
#include "Seller.h"
#include "Buyer.h"
#include "Megauser.h"
#include "Address.h"
#include "Date.h"
#include "Feedback.h"
#include "Order.h"
#include "Product.h"
#include "Array.h"


using namespace std;

class System
{
private: //Class variables
	//User** users;
	Array<User*> users;

private: //Class helper variables
	int numOfSellers;
	int numOfBuyers;
	int numOfMegauser;
public:
	static constexpr int MAX_LEN_NAME = 21;
	static constexpr int ALLOCATION_ERROR = -1;

public:  //Constractur, Move, Copy, Destractor
	System();
	System(const System& other) = delete;
	System(System&& other) = delete;
	~System();

public: //Class Public Methods
	bool addSeller(const string& name, const string& password, Address& address, bool print);
	bool addBuyer(const string& name, const string& password, Address& address, bool print);
	bool addMegaUser(const string& name, const string& password, Address& address, bool print);
	bool addProductToSeller(const string& sellerName, const string& productName, const double price, const int category);
	bool addFeedbackToSeller(const string& buyerName, const string& sellerName, const int day, const int month, const int year, const string& text); //I used buyer but add from seller
	void addProductToWishList(const string& buyerName, const int prod_serial);
	Order* OpenNewOrderList(const string& Buyername, Buyer** buyer);
	bool payOrder(Buyer* buyer, int order_sir);
	bool showProductByName(const string& data, const string& type) const;
	void printTheSellerList() const;
	void PrintTheBuyerList() const;
	void PrintTheMegaUserList() const;

	//GETES
	int getNumberOfSellers() const;
	int getNumbersOfBuyers() const;
	int getNumbersOfMegauser() const;

	//HELPER
	Array<User*> getUsersList() const;
	Seller* sellerIsExist(const string& name) const;
	Buyer* buyerIsExist(const string& name) const;
	Megauser* MegauserIsExist(const string& name) const;
	User* userIsExist(const string& name) const;
	Product* HelperFindACeratinProduct(const int prod_serial, bool& found);
	bool ActivateAddfromBuyer(Buyer* buyer, int sir, Order* order);
	void DeleteLastOrder(Buyer* buyer);
	void SaveUsers(const char* file_name);
	void LoadUsers(const string& file_name);
	void getStrFromFile(ifstream& in, string& str, int len);

	//OPERATORS
	const System& operator+=(Seller& other);
	const System& operator+=(Buyer& other);
	const System& operator+=(Megauser& other);
};
#endif // _SYSTEM_H