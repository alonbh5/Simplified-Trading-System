#include "System.h"
//---------------------------------------------------------------------------------------------------//
System::System()
{
	numOfBuyers = 0;
	numOfSellers = 0;
	numOfMegauser = 0;
}
//---------------------------------------------------------------------------------------------------//
System::~System()
{
	//cout<<"d'ctor of system"<<endl;
	int idx;
	int length = users.getLogical();

	for (idx = 0; idx < length; idx++)
		delete users.getArr()[idx];

}
//---------------------------------------------------------------------------------------------------//
bool System::addSeller(const string& name, const string& password, Address& address, bool print)
{
	User* user = userIsExist(name);
	if (user)//!=nullptr
	{
		cout << "The  user " << name << " is already Exist in the system\n";
		return false;
	}
	Seller* seller = new Seller(name, password, address);
	*this += (*seller);
	if (print)
		cout << "The Seller " << seller->getName() << " Added to system!\n";
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool System::addBuyer(const string& name, const string& password, Address& address, bool print)
{
	User* user = userIsExist(name);
	if (user)//!=nullptr
	{

		cout << "The  user " << name << " is already Exist in the system\n";
		return false;
	}
	Buyer* buyer = new Buyer(name, password, address);
	*this += (*buyer);
	if (print)
		cout << "The Buyer " << buyer->getName() << " Added to system!\n";
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool System::addMegaUser(const string& name, const string& password, Address& address, bool print)
{
	User* user = userIsExist(name);
	if (user)//!=nullptr
	{
		cout << "The  user " << name << " is already Exist in the system\n";
		return false;
	}
	Megauser* MegaUser = new Megauser(name, password, address);
	*this += (*MegaUser);
	if (print)
		cout << "The Megauser " << MegaUser->getName() << " Added to system!\n";
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool System::addProductToSeller(const string& sellerName, const string& productName, const double price, const int category)
{
	bool flag = false;
	Seller* sellerTemp = sellerIsExist(sellerName);

	if (sellerTemp) //Seller\Megauser is exist
	{
		Product* newProduct = new Product(productName, (category - 1), (*sellerTemp), price);
		if (sellerTemp)
			flag = sellerTemp->addNewProductforList(newProduct);

		if (flag)  // if != NULL
		{
			cout << "Product add succsefully!" << endl;
			return true;
		}
		else
		{
			cout << "Error: Adding the product to " << sellerName << "'s products list\n";
			delete newProduct;
		}
	}
	cout << "Seller " << sellerName << " doesn't exist, can't add the product";
	return false;
}
//---------------------------------------------------------------------------------------------------//
bool System::addFeedbackToSeller(const string& buyerName, const string& sellerName, const int day, const int month, const int year, const string& text)
{

	if (buyerName == sellerName)
	{
		cout << "Buyer name is The same as Seller name - Exiting" << endl;
		return false;
	}

	Seller* seller = sellerIsExist(sellerName);
	Buyer* buyer = buyerIsExist(buyerName);

	if (!seller || !buyer) //seller or buyer dosen't exist in the system
	{
		cout << "The seller Or buyer you write doesn't Exist\n";
		return false;
	}


	if (buyer->DidyouBuyfromSeller(seller)) //checking if Buyer buy a product from seller
	{
		Date date(day, month, year); //creating Date object
		Feedback* feedback = new Feedback(text, buyer, date); //creating feedback object
		if (seller->addNewFeedbackforList(feedback)) // !=nullptr
		{
			cout << "Feedback Added!\n";
			return true;
		}
		else
		{
			cout << "Feedback Failed: Unknown\n";
			delete feedback;
		}
	}
	else
		cout << "Feedback Failed: the buyer: " << buyer->getName() << " didn't buy product from Seller " << seller->getName() << endl;
	return false;
}
//---------------------------------------------------------------------------------------------------//
void System::addProductToWishList(const string& buyerName, const int prod_serial)
{
	bool found = false;
	Buyer* buyer = nullptr;
	Product* data = nullptr;

	buyer = buyerIsExist(buyerName);
	if (!buyer)
	{
		cout << "Sorry Buyer was not found" << endl;
		return;
	}

	data = HelperFindACeratinProduct(prod_serial, found);
	//The Product didn't found
	if (found)
	{
		if (data->getSeller().getName() == buyer->getName())
		{
			cout << "You cannot order a product from yourself\n";
			return;
		}

		if (buyer->FindinWIshlist(data)) // The product is already in wishlist
		{
			cout << "The Product " << data->getName() << " is already in " << buyer->getName() << " WishList\n";
			return;
		}
		if (data->getAvailable())  // The product is'nt in wishlist
		{
			buyer->addNewProductforWishList(data);
			cout << "Product " << prod_serial << " was added to " << buyerName << " successfully!" << endl;
		}
		else
			cout << "Sorry! the item you are looking for is Sold!" << endl;
	}

}
//---------------------------------------------------------------------------------------------------//
Order* System::OpenNewOrderList(const string& Buyername, Buyer** buyer)
{
	bool found = false, flag = true;
	Product* prod = nullptr;
	Order* order = nullptr;

	(*buyer) = buyerIsExist(Buyername);
	if (!(*buyer))
	{
		cout << "The buyer " << Buyername << " doesn't Exist\n";
		return nullptr;
	}
	order = new Order(**buyer);
	(*buyer)->addOrdertoHistory(order);
	return order;
}
//---------------------------------------------------------------------------------------------------//
bool System::payOrder(Buyer* buyer, int order_sir)
{
	// return true only if order was found and payed
	bool found = false;
	int i;

	for (i = 0; i < buyer->getLogsize_history() && !found; i++)
	{
		if (buyer->getOrderhistory()[i]->getOrderSerialNumber() == order_sir)
		{
			found = true;
			if (buyer->getOrderhistory()[i]->Payment())
			{
				for (int j = 0; j < buyer->getOrderhistory()[i]->getLogsize_orderlist(); j++) //removing all the product from order
				{
					buyer->getOrderhistory()[i]->getorderlist()[j]->setAvailable(false);
					buyer->getOrderhistory()[i]->getorderlist()[j]->setBuyer(buyer);
					buyer->removeProdctfromWislist(buyer->getOrderhistory()[i]->getorderlist()[j]);
				}
				return true;
			}
			else
				return false;
		}
	}
	cout << "Order number " << order_sir << " was not found!" << endl;
	return false;
}
//---------------------------------------------------------------------------------------------------//
bool System::showProductByName(const string& data, const string& type) const
{
	//the function printing the products in the system.
	//if type==Availbale, the function will print only the available "name"'s products
	//if type==All, the function will print all the products in the system by "name"
	int idx, idx_products;
	bool flag = false;
	int counter = 1;
	vector<Product*> currList;
	Product* currProduct = nullptr;

	cout << "============ Showing " << type << " Products By The Name " << data << " ============\n";
	int length = this->users.getLogical();

	for (idx = 0; idx < length; idx++)
	{
		Seller* currSeller = dynamic_cast<Seller*>(users.getArr()[idx]);
		if (currSeller)
		{
			int tempIndex = currSeller->AmountOfProductList();
			currList = currSeller->getAllProducts();
			for (idx_products = 0; idx_products < tempIndex; idx_products++)
			{
				currProduct = currList[idx_products];
				if (currProduct->getName() == data)
				{
					if ((type == "Available") && currProduct->getAvailable()) // print Available products
					{
						cout << counter++ << ") " << *currProduct << endl;
						flag = true;
					}
					if (type == "All") //print all products by the name
					{
						cout << counter++ << ") " << *currProduct << endl;
						flag = true;
					}
				}
			}
		}
	}
	if (!flag && (type == "Available"))
		cout << "Sorry, we didn't find Available item by the name " << data << endl;
	else if (!flag && (type == "All"))
		cout << "Sorry, we didn't find product by the name " << data << endl;
	return flag;
}
//---------------------------------------------------------------------------------------------------//
void System::PrintTheBuyerList() const
{
	cout << "==========================Buyers List==========================\n";
	if (numOfBuyers == 0)
	{
		cout << "No Buyers in The List\n";
		return;
	}
	int count, idx;
	count = 1;
	int length = this->users.getLogical();
	for (idx = 0; idx < length; idx++)
	{

		if (typeid(*(users.getArr()[idx])) == typeid(Buyer))
		{
			cout << (count++) << ") ";
			Buyer* tempBuyer = dynamic_cast<Buyer*>(users.getArr()[idx]);
			cout << *tempBuyer << "\n"
				<< "---------------------------------------------------------------------------------\n";
		}
	}
}
//---------------------------------------------------------------------------------------------------//
void System::PrintTheMegaUserList() const
{
	cout << "==========================MegaUser (buyer-seller) List==========================\n";
	if (numOfMegauser == 0)
	{
		cout << "No MegaUser(buyer&seller) in The List\n";
		return;
	}
	int count, idx;
	count = 1;
	int length = this->users.getLogical();
	for (idx = 0; idx < length; idx++)
	{

		Megauser* tempMega = dynamic_cast<Megauser*>(users.getArr()[idx]);
		if (tempMega)
		{
			cout << (count++) << ") ";
			cout << *tempMega << "\n"
				<< "---------------------------------------------------------------------------------\n";
		}
	}
}
//---------------------------------------------------------------------------------------------------//
void System::printTheSellerList() const
{
	cout << "==========================SELLERS List==========================\n";
	if (numOfSellers == 0)
	{
		cout << "No Sellers in The List\n";
		return;
	}

	int count, idx;
	count = 1;
	int length = this->users.getLogical();
	for (idx = 0; idx < length; idx++)
	{
		if (typeid(*(users.getArr()[idx])) == typeid(Seller))
		{
			cout << (count++) << ") ";
			Seller* tempBuyer = dynamic_cast<Seller*>(users.getArr()[idx]);
			cout << *tempBuyer << "\n"
				<< "---------------------------------------------------------------------------------\n";
		}
	}

}
//---------------------------------------------------------------------------------------------------//
int System::getNumberOfSellers() const { return (numOfSellers); }
//---------------------------------------------------------------------------------------------------//
int System::getNumbersOfBuyers() const { return (numOfBuyers); }
//---------------------------------------------------------------------------------------------------//
int System::getNumbersOfMegauser() const { return (numOfMegauser); }
//---------------------------------------------------------------------------------------------------//
Array<User*> System::getUsersList() const { return users; }
//---------------------------------------------------------------------------------------------------//
Seller* System::sellerIsExist(const string& name) const
{
	//AUX function for checking if the user name is exist
	int idx;
	int length = this->users.getLogical();
	for (idx = 0; idx < length; idx++)
	{
		Seller* tempSeller = dynamic_cast<Seller*>(users.getArr()[idx]);
		if (tempSeller)
		{
			if (tempSeller->getName() == name)
				return (tempSeller);
		}
	}
	return nullptr;
}
//---------------------------------------------------------------------------------------------------//
Buyer* System::buyerIsExist(const string& name) const
{
	//AUX function for checking if the user name is exist
	int idx;
	int length = this->users.getLogical();
	for (idx = 0; idx < length; idx++)
	{
		Buyer* tempBuyer = dynamic_cast<Buyer*>(users.getArr()[idx]);
		if (tempBuyer)
		{
			if (tempBuyer->getName() == name)
				return (tempBuyer);
		}
	}
	return nullptr;
}
//---------------------------------------------------------------------------------------------------//
User* System::userIsExist(const string& name) const
{
	//AUX function for checking if the user name is exist
	int idx;
	int length = this->users.getLogical();
	for (idx = 0; idx < length; idx++)
	{
		if (this->users.getArr()[idx]->getName() == name)
			return (users.getArr()[idx]);
	}
	return nullptr;

}
//---------------------------------------------------------------------------------------------------//
Megauser* System::MegauserIsExist(const string& name) const
{
	//AUX function for checking if the user name is exist
	int idx;
	int length = this->users.getLogical();
	for (idx = 0; idx < length; idx++)
	{
		Megauser* tempMegauser = dynamic_cast<Megauser*>(users.getArr()[idx]);
		if (tempMegauser)
		{
			if (tempMegauser->getName() == name)
				return (tempMegauser);
		}
	}
	return nullptr;
}
//---------------------------------------------------------------------------------------------------//
Product* System::HelperFindACeratinProduct(const int prod_serial, bool& found)
{
	Product* product = nullptr;
	int length = this->users.getLogical();
	for (int index = 0; index < length && !found; index++)
	{
		Seller* tempSeller = dynamic_cast<Seller*>(users.getArr()[index]);
		if (tempSeller)
		{
			product = tempSeller->findCertainProductInList(prod_serial);
			if (product) //Data found
				found = true;
		}

	}
	if (!found)
		cout << "Sorry - " << prod_serial << " was not found!" << endl;
	return product;
}
//---------------------------------------------------------------------------------------------------//
bool System::ActivateAddfromBuyer(Buyer* buyer, int sir, Order* order)
{
	return (buyer->AddProductToACertainOrder(order, sir));
}
void System::DeleteLastOrder(Buyer* buyer)
{
	buyer->removeLastOrderFromHistory();
}
//---------------------------------------------------------------------------------------------------//
const System& System::operator+=(Seller& other)
{
	users += &other;
	numOfSellers++;
	return *this;
}
//---------------------------------------------------------------------------------------------------//
const System& System::operator+=(Buyer& other)
{
	users += &other;
	numOfBuyers++;
	return *this;
}
//---------------------------------------------------------------------------------------------------//
const System& System::operator+=(Megauser& other)
{
	users += &other;
	numOfMegauser++;
	return *this;
}
//---------------------------------------------------------------------------------------------------//
void System::SaveUsers(const char* file_name)
{
	ofstream out_file(file_name, ios::trunc);
	char dolimter = ' ';
	int len = this->users.getLogical();
	cout << "Saving System DB..." << endl;
	out_file << this->users.getLogical() << endl;
	for (int i = 0; i < len; i++)
	{
		out_file << typeid(*(this->users.getArr()[i])).name() + 6 << dolimter;
		this->users.getArr()[i]->save(out_file);
		out_file << endl;
	}
	cout << "Saving Complete!" << endl;
	out_file.close();
}
//---------------------------------------------------------------------------------------------------//
void System::LoadUsers(const string& file_name)
{
	ifstream in_file(file_name, ios::in);
	string type;
	int runlen;
	Buyer* buyer;
	Seller* seller;
	Megauser* megauser;

	if (!in_file)
		return;
	else
		cout << "Loading Previos System DB..." << endl;
	in_file >> runlen;
	for (int i = 0; i < runlen; i++)
	{
		in_file >> type;

		if (type == "Buyer")
		{
			buyer = new Buyer(in_file);
			*this += *buyer;

		}
		else if (type == "Seller")
		{
			seller = new Seller(in_file);
			*this += *seller;
		}
		else if (type == "Megauser")
		{
			megauser = new Megauser(in_file);
			*this += *megauser;
		}
		else
		{
			cout << "Error in reading file\n";
			exit(1);
		}


	}

	cout << endl << "Loading Complete!" << endl;

}