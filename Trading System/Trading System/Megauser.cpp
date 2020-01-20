#include "Megauser.h"

//---------------------------------------------------------------------------------------------------//
Megauser::Megauser(const char* name, const char* password, const Address& address):
	User(name, password, address), Seller(name, password, address), Buyer(name, password, address)
{
	//cout << "In MegaUser C'tor\n";
}
//---------------------------------------------------------------------------------------------------//
Megauser::Megauser(Megauser&& other):User(move(other)),Seller(move(other)),Buyer(move(other))
{
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
void Megauser::save(ofstream& out_file)
{
	User::save(out_file);
}
//---------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const Megauser& obj)
{
	os << "UserName: " << obj.name << " | Address: " << obj.address
		<< "He has " << obj.getLogsize_wishlist() << " items in Wish list." << endl
		<< "He Ordered :" << obj.getLogsize_history() << " Times in the past." << endl
		<< "He selles : " << obj.AmountOfProductList() << " items." << endl
		<<"He has " <<obj.AmountOfFeedback()<<" Feedback."<<endl;
	return os;
}
//---------------------------------------------------------------------------------------------------//
