#include "Product.h"

int Product::conterSerial = 1000;
//---------------------------------------------------------------------------------------------------//
static const string CategoryPro[] = { "Kids", "Electrical", "Office", "Clothing" };
//---------------------------------------------------------------------------------------------------//
Product::Product(const string& name, const int category, const Seller& seller, const double price) :
	serialnumber(++conterSerial), seller(seller), available(available)
{
	//cout << "in ctor PRODUCT\n" << endl;
	setAvailable(true);
	setName(name);
	setPrice(price);
	setCategory(category);
	setBuyer();
}
//---------------------------------------------------------------------------------------------------//
Product::Product(const Product& other) :serialnumber(++conterSerial), price(other.price), seller(other.seller)
{
	//cout << "In PRODUCT copy c'tor" << name << endl;
	setName(other.name);
	setAvailable(other.available);
	int temp = (int)other.category;
	setCategory(temp);
}

//---------------------------------------------------------------------------------------------------//
Product::~Product()
{
	//cout << "In PRODUCT d'tor for " << name << endl;
	this->buyer = nullptr;
	//this->seller = nullptr;
}
//---------------------------------------------------------------------------------------------------//
bool Product::setName(const string& name)
{
	//The function check the input and set the Name
	if (name.size() >= MAX_LEN_NAME)
	{
		cout << "The name must contain " << (MAX_LEN_NAME - 1) << " letters or less." << endl;
		return false;
	}
	this->name = name;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Product::setPrice(const double price)
{
	//The function check the price and set the pricr
	if (price < 0)
	{
		cout << "not a Price - Price changed to 1 \n";
		return false;
	}
	this->price = price;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Product::setCategory(const int category)
{
	this->category = (enum eCategory)category;
	return true;
}
//---------------------------------------------------------------------------------------------------//
void Product::setAvailable(const bool flag)
{
	if (flag)
		this->available = true;
	else
		this->available = false;
}
//---------------------------------------------------------------------------------------------------//
void Product::setBuyer(const Buyer* buyer) { this->buyer = buyer; }
//---------------------------------------------------------------------------------------------------//
const string& Product::getName() const { return name; };
//---------------------------------------------------------------------------------------------------//
double Product::getPrice() const { return price; };
//---------------------------------------------------------------------------------------------------//
int Product::getCategory() const { return (int)category; };
//---------------------------------------------------------------------------------------------------//
int Product::getSerialNumber() const { return serialnumber; }
//---------------------------------------------------------------------------------------------------//
const Seller& Product::getSeller() const
{
	//The function return the address of the product's seller
	return seller;
}
//---------------------------------------------------------------------------------------------------//
bool Product::getAvailable() const
{
	//The function return the availablity of the product
	//True - Available, False- Not avaliable
	return this->available;
}
//---------------------------------------------------------------------------------------------------//
int Product::getHowManyProductsInSystem() const
{
	//The function return the num of the products
	return(conterSerial - 1000 + 1);
}
//---------------------------------------------------------------------------------------------------//
void Product::print() const
{
	cout << "Name of product: " << name << " | Category:" << CategoryPro[category]
		<< " | Price:" << price << " | Serial Number: " << serialnumber << " | Name of Seller: " << seller.getName();
	if (getAvailable())
		cout << " | Availabilty: AVAILABLE\n";
	else
		cout << " | Availabilty: NOT AVAILABLE\n";
}
//---------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const Product& prod)
{
	os << "Name of product : " << prod.name << " | Category : " << CategoryPro[prod.category]
		<< " | Price:" << prod.price << " | Serial Number: " << prod.serialnumber
		<< " | Name of Seller: " << prod.seller.getName();

	if (prod.getAvailable())
		os << " | Availabilty: AVAILABLE\n";
	else
		os << " | Availabilty: NOT AVAILABLE\n";
	return os;
}
//---------------------------------------------------------------------------------------------------//