#include "Buyer.h"

Buyer::Buyer(ifstream& inFile) :User(inFile)
{
}

//---------------------------------------------------------------------------------------------------//
Buyer::Buyer(const string& name, const string& password, const Address& home_address) : User(name, password, home_address)
{
	//cout << "in c'tor Buyer" << endl;
}

//---------------------------------------------------------------------------------------------------//
Buyer::~Buyer()
{
	//cout << "in d'tor Buyer" << endl;
	int length = this->getLogsize_wishlist();
	vector<Product*>::iterator W_itr = Wishlist.begin();
	vector<Product*>::iterator W_itrEnd = Wishlist.end();

	vector<Order*>::iterator O_itr = order_history.begin();
	vector<Order*>::iterator O_itrEnd = order_history.end();

	Wishlist.clear(); //The seller is responsable of the dynamic allocation of products;
	for (; O_itr != O_itrEnd; ++O_itr)
		delete (*O_itr);
	order_history.clear();


}
//---------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const Buyer& obj)
{
	os << "UserName: " << obj.name << " | Address: " << obj.address
		<< " | Products: " << obj.getLogsize_wishlist() << " items in Wish list." << endl
		<< "| He Ordered :" << obj.getLogsize_history() << " Times in the past." << endl;
	return os;
}
//---------------------------------------------------------------------------------------------------//
bool Buyer::operator>(const Buyer& other)
{
	return (this->calculateWishlist() > other.calculateWishlist());
}
//---------------------------------------------------------------------------------------------------//
bool Buyer::operator<(const Buyer& other)
{
	return (this->calculateWishlist() < other.calculateWishlist());
}
//---------------------------------------------------------------------------------------------------//
int Buyer::getPhysize_wishlist() const { return (int)this->Wishlist.capacity(); }
//---------------------------------------------------------------------------------------------------//
int Buyer::getLogsize_wishlist() const { return (int)this->Wishlist.size();; }
//---------------------------------------------------------------------------------------------------//
vector<Order*> Buyer::getOrderhistory() const { return(this->order_history); }
//---------------------------------------------------------------------------------------------------//
vector<Product*> Buyer::getWishlist() const { return (this->Wishlist); }
//---------------------------------------------------------------------------------------------------//
int Buyer::getPhysize_history() const { return (int)this->order_history.capacity(); }
//---------------------------------------------------------------------------------------------------//
int Buyer::getLogsize_history() const { return (int)this->order_history.size(); }
//---------------------------------------------------------------------------------------------------//
void Buyer::show() const
{
	//print buyer info
	cout << "Username: " << name << " | Address: ";
	this->address.show();
	cout << " | Products: " << this->getLogsize_wishlist() << " items in Wish list." << endl;
	cout << "| He Ordered :" << this->getLogsize_history() << " Times in the past." << endl;
}
//---------------------------------------------------------------------------------------------------//
void Buyer::showwithpass() const
{
	//print buyer info wish password
	cout << "Buyer username is " << name << " from " << endl;
	this->address.show();
	cout << " His password is  " << password << endl;
	cout << ", He has " << this->getLogsize_wishlist() << " items in Wish list." << endl;
	cout << " He Ordered " << this->getLogsize_history() << "Times in the past." << endl;
}
//---------------------------------------------------------------------------------------------------//
void Buyer::save(ofstream& out_file)
{
	User::save(out_file);
}
//---------------------------------------------------------------------------------------------------//
bool Buyer::FindinWIshlist(const Product* FindMe) const
{
	//get a prodct and return true if it in buyers wishlist
	//else return false
	bool res = false;
	int sir = FindMe->getSerialNumber();
	vector<Product*>::const_iterator W_itr = this->Wishlist.begin();
	vector<Product*>::const_iterator W_itrEnd = this->Wishlist.end();

	for (; W_itr != W_itrEnd && !res; ++W_itr)
		if (sir == (*W_itr)->getSerialNumber())
			res = true;
	return res;
}
//---------------------------------------------------------------------------------------------------//
bool Buyer::DidyouBuyfromSeller(const Seller* seller) const
{
	//gets a seller X (by ptr) and check if the buyer has ever bougth from X
	bool res = false;
	vector<Order*>::const_iterator O_itr = order_history.begin();
	vector<Order*>::const_iterator O_itrEnd = order_history.end();

	for (; O_itr != O_itrEnd; ++O_itr)
		res = (*O_itr)->DidBuyerBuyFromSeller(seller);
	return res;
}
//---------------------------------------------------------------------------------------------------//
void Buyer::addNewProductforWishList(Product* p_data)
{
	Wishlist.push_back(p_data);
}
//---------------------------------------------------------------------------------------------------//
bool Buyer::removeProdctfromWislist(Product* p_data)
{
	//find p date and remove it from wishlist, update logsize and shrink list..
	//do not deletes product!
	bool res = false;
	int sir;
	sir = p_data->getSerialNumber();
	vector<Product*>::iterator W_itr = this->Wishlist.begin();
	vector<Product*>::iterator W_itrEnd = this->Wishlist.end();

	for (; W_itr != W_itrEnd && !res; ++W_itr)
		if (sir == (*W_itr)->getSerialNumber())
			res = true;
	if (res)
	{
		--W_itrEnd;
		--W_itr;
		if (W_itr == W_itrEnd)
			Wishlist.pop_back();
		else // W_itr!=W_itrEnd
		{

			iter_swap(W_itr, W_itrEnd);
			Wishlist.pop_back();
		}
	}
	return res;
}
//---------------------------------------------------------------------------------------------------//
void Buyer::addOrdertoHistory(Order* order)
{
	//add order to order list
	order_history.push_back(order);
}
//---------------------------------------------------------------------------------------------------//

void Buyer::removeLastOrderFromHistory()
{
	this->order_history.pop_back();
}
//---------------------------------------------------------------------------------------------------//
bool Buyer::PrintWishlist() const
{
	//print all wishlist
	vector<Product*>::const_iterator W_itr = this->Wishlist.begin();
	vector<Product*>::const_iterator W_itrEnd = this->Wishlist.end();

	cout << " ======== Wishlist of " << this->name << " ========\n";
	if (this->getLogsize_wishlist() == 0)
	{
		cout << "WishList is Empty\n";
		return false;
	}
	for (; W_itr != W_itrEnd; ++W_itr)
	{
		cout << "---------------------" << endl;
		cout << *(*W_itr) << endl;
	}
	return true;
}
//---------------------------------------------------------------------------------------------------//
void Buyer::printOrder() const
{
	//print all orders 
	vector<Order*>::const_iterator O_itr = order_history.begin();
	vector<Order*>::const_iterator O_itrEnd = order_history.end();
	for (; O_itr != O_itrEnd; ++O_itr)
	{
		cout << "---------------------" << endl;
		(*O_itr)->print();
		cout << endl;
	}
}
//---------------------------------------------------------------------------------------------------//
int Buyer::printOrderNotpaid() const
{
	//print all Unpaid orders 
	vector<Order*>::const_iterator O_itr = order_history.begin();
	vector<Order*>::const_iterator O_itrEnd = order_history.end();
	int count = 0;
	for (; O_itr != O_itrEnd; ++O_itr)
	{
		cout << "---------------------" << endl;
		if (!(*O_itr)->getPayed())
		{
			count++;
			(*O_itr)->print();
			cout << endl;
		}

	}
	return count;
}
//---------------------------------------------------------------------------------------------------//
double Buyer::calculateWishlist() const
{
	double res = 0.0;
	vector<Product*>::const_iterator W_itr = this->Wishlist.begin();
	vector<Product*>::const_iterator W_itrEnd = this->Wishlist.end();

	for (; W_itr != W_itrEnd; ++W_itr)
		res += (*W_itr)->getPrice();
	return res;
}
//---------------------------------------------------------------------------------------------------//
bool Buyer::AddProductToACertainOrder(Order* order, const int sir)
{
	Product* prod = nullptr;
	vector<Product*>::iterator W_itr = this->Wishlist.begin();
	vector<Product*>::iterator W_itrEnd = this->Wishlist.end();

	bool found = false;
	for (; W_itr != W_itrEnd && !found; ++W_itr)
	{
		if (sir == (*W_itr)->getSerialNumber())
		{
			prod = (*W_itr);
			found = true;
			if (!prod->getAvailable())
			{
				cout << "The product is'nt avalibale removing it from wishlist!\n";
				this->removeProdctfromWislist(prod);
				return false;
			}
			else
			{
				if (order->AddProducttolist(prod))
					return true;
				else
					return false;
			}
		}
	}
	if (!found)
		cout << "Wrong serial number\n";
	return false;
}
//---------------------------------------------------------------------------------------------------//

