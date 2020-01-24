#include "Order.h"
//---------------------------------------------------------------------------------------------------//
Order::Order(const Buyer& buyer) :OrderSerialNumber(++OrderCounter), buyer(buyer)
{
	this->Totalprice = 0.0;
	this->Payed = false;
}
//---------------------------------------------------------------------------------------------------//
Order::~Order()
{
	//cout << "In desractor of Order\n";
	vector<Product*>::iterator P_itr = order_list.begin();
	vector<Product*>::iterator P_itrEnd = order_list.end();

	order_list.clear();
}
//---------------------------------------------------------------------------------------------------//
bool Order::setprice(double price)
{
	//set price to what you want only if price is postive 
	if (price < 0.0)
		return false;
	this->Totalprice = price;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Order::setPayed()
{
	//change order to payed
	this->Payed = true;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Order::getPayed() const { return this->Payed; }
//---------------------------------------------------------------------------------------------------//
double Order::getprice() const { return (this->Totalprice); }
//---------------------------------------------------------------------------------------------------//
const Buyer& Order::getbuyer() const { return (this->buyer); }
//---------------------------------------------------------------------------------------------------//
int Order::getOrderSerialNumber() const { return (this->OrderSerialNumber); }
//---------------------------------------------------------------------------------------------------//
vector<Product*> Order::getorderlist() const { return (this->order_list); }
//---------------------------------------------------------------------------------------------------//
int Order::getPhysize_orderlist() const { return((int)this->order_list.capacity()); }
//---------------------------------------------------------------------------------------------------//
int Order::getLogsize_orderlist() const { return((int)this->order_list.size()); }
//---------------------------------------------------------------------------------------------------//
void Order::print() const
{
	vector<Product*>::const_iterator P_itr = order_list.begin();
	vector<Product*>::const_iterator P_itrEnd = order_list.end();
	//print order info
	cout << "Order information:" << endl;
	cout << "Order Number:" << this->OrderSerialNumber << endl;
	cout << "=========================================================================" << endl;
	cout << "For Buyer:" << this->buyer.getName() << "\nBought :" << endl;
	for (; P_itr != P_itrEnd; ++P_itr)
	{
		cout << "------------------------------------------------------" << endl;
		(*P_itr)->print();
		cout << "------------------------------------------------------" << endl;
	}

	cout << "Total Price:" << this->Totalprice << endl;
	if (this->getPayed())
		cout << "Order status: Payment completed" << endl;
	else
		cout << "Order status: Payment Not completed!" << endl;
	cout << "=========================================================================" << endl;
}
//---------------------------------------------------------------------------------------------------//
//this function add to otder list 
	//its checks if :
	//1. the prod_to_add is in buyers wishlist (if not return false)
	//2.if it allready exiist in current list (return false)
	//3. check if availbale 
	//if 1 2 and 3 are good, add it, update the price and return true
bool Order::AddProducttolist(Product* prod_to_add)
{
	bool flag, res;
	int sir;
	flag = true;
	res = false;
	vector<Product*>::iterator P_itr = order_list.begin();
	vector<Product*>::iterator P_itrEnd = order_list.end();

	if (this->buyer.getLogsize_wishlist() == 0) //case no wishlist
	{
		cout << "Current Buyer's Wishlist is empty " << endl;
		return res;
	}
	else
	{
		if (prod_to_add->getAvailable()) //if the item is Available
		{
			if (this->buyer.FindinWIshlist(prod_to_add)) //if it existet in buyers wishlist
			{
				sir = prod_to_add->getSerialNumber();
				for (; P_itr != P_itrEnd && flag; ++P_itr)
				{
					if ((*P_itr)->getSerialNumber() == sir)//check that the item is not allready there
						flag = false;
				}
				if (!flag)
				{
					cout << "Item is already in current order! " << endl;
				}
				else //add to order list/*
				{
					this->Totalprice += prod_to_add->getPrice(); //update the total price}
					order_list.push_back(prod_to_add);
					cout << "Item had been added to order! " << endl;
					res = true;
				}
			}
		}
		else
		{
			cout << "Item is not Available (sold)" << endl;
			return res;
		}
		return res;
	}
}
//---------------------------------------------------------------------------------------------------//
///presuming all products in order are at buyers wish list!!!!!!!!!!!!!!!!!!!!!!!!!
//check if we can make an order (price not 0 and every product is Available - not sold) and order not payed allreadu
//mark all pruodcts as sold (not avialble)
//remove products from wishlist of relevent buyer
//mark order as payed
//add this order to buyers history 
//print the order.
bool Order::Payment()
{//The function isn't remove the products from buyer's wishlist.
	//system will change and remove all them.
	bool res;
	res = false;

	if ((this->getprice() == 0.0))
		cout << "No items in current order" << endl;
	else
		if ((this->getPayed()))
			cout << "Order Already Got Paid!" << endl;
		else
			if (!(this->IsAllAvailable()))
				cout << "Some of the products already got sold, please remove it from the order" << endl;
			else
			{
				this->setPayed();
				this->print();
				res = true;
			}
	return res;
}
//---------------------------------------------------------------------------------------------------//
bool Order::calculateprice()
{
	//caculate price by the prodact list in the order

	double priceX = 0.0;
	vector<Product*>::iterator P_itr = order_list.begin();
	vector<Product*>::iterator P_itrEnd = order_list.end();

	if (this->getLogsize_orderlist() == 0)
		return false;

	for (; P_itr != P_itrEnd; ++P_itr)
		priceX += (*P_itr)->getPrice();
	setprice(priceX);
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Order::removeFromOrderList(Product* prod_to_del)
{
	//find prod_to_del and remove it from order list, update logsize and shrink list..
	//do not deletes product!
	bool res = false;
	int sir;
	vector<Product*>::iterator P_itr = order_list.begin();
	vector<Product*>::iterator P_itrEnd = order_list.end();

	sir = prod_to_del->getSerialNumber();
	for (; P_itr != P_itrEnd; ++P_itr)
	{
		if (sir == (*P_itr)->getSerialNumber())
			res = true;
	}

	if (res)
	{
		--P_itr;
		--P_itrEnd;
		if (P_itr == P_itrEnd)
			order_list.pop_back();
		else // P_itr!=P_itrEnd
		{
			iter_swap(P_itr, P_itrEnd);
			order_list.pop_back();
		}
	}
	return res;
}
//---------------------------------------------------------------------------------------------------//
bool Order::IsAllAvailable() const
{
	//check if all the products in the order are abialible
	bool res = true;
	vector<Product*>::const_iterator P_itr = order_list.begin();
	vector<Product*>::const_iterator P_itrEnd = order_list.end();

	for (; P_itr != P_itrEnd; ++P_itr)
		if ((*P_itr)->getAvailable() == false)
			res = false;

	return res;
}

//---------------------------------------------------------------------------------------------------//
void Order::ClearNotAvailable()
{
	//delete all non availble products from order
	vector<Product*>::iterator P_itr = order_list.begin();
	vector<Product*>::iterator P_itrEnd = order_list.end();
	vector<Product*>::iterator P_itrAddTheLast = --(order_list.end());

	for (; P_itr != P_itrEnd; ++P_itr)
	{
		if (!(*P_itr)->getAvailable())
		{
			if (P_itr == P_itrAddTheLast)
				order_list.pop_back();
			else
			{
				iter_swap(P_itr, P_itrAddTheLast);
				order_list.pop_back();
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------//
bool Order::DidBuyerBuyFromSeller(const Seller* seller) const
{
	bool res = false;
	const string seller_name = seller->getName();
	vector<Product*>::const_iterator P_itr = order_list.begin();
	vector<Product*>::const_iterator P_itrEnd = order_list.end();

	for (; P_itr != P_itrEnd && !res; ++P_itr)
		if (seller_name == (*P_itr)->getSeller().getName())
			//if the name of the curent prudct seller is what we are looking
			if (this->getPayed())
				res = true;
	return res;
}
//---------------------------------------------------------------------------------------------------//
int Order::OrderCounter = 10000;