#include "Megauser.h"



Megauser::Megauser(ifstream& in) :User(in), Seller(in), Buyer(in)
{
}

//---------------------------------------------------------------------------------------------------//
Megauser::Megauser(const string& name, const string& password, const Address& address) :
	User(name, password, address), Seller(name, password, address), Buyer(name, password, address)
{
	//cout << "In MegaUser C'tor\n";
}
//---------------------------------------------------------------------------------------------------//
Megauser::~Megauser()
{
	//cout << "In Megauser d'tor\n";
}
//---------------------------------------------------------------------------------------------------//
void Megauser::show() const
{
	Seller::show();
	Buyer::show();
}
//---------------------------------------------------------------------------------------------------//
void Megauser::save(ofstream& out_file)
{
	Seller::save(out_file);

}
//---------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const Megauser& obj)
{
	os << "UserName: " << obj.name << " | Address: " << obj.address
		<< "He has " << obj.getLogsize_wishlist() << " items in Wish list." << endl
		<< "He Ordered :" << obj.getLogsize_history() << " Times in the past." << endl
		<< "He selles : " << obj.AmountOfProductList() << " items." << endl
		<< "He has " << obj.AmountOfFeedback() << " Feedback." << endl;
	return os;
}
//---------------------------------------------------------------------------------------------------//