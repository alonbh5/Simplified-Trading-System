#include"Seller.h"

Seller::Seller(ifstream& inFile) :User(inFile)
{
	inFile >> *this;
}

Seller::Seller(const string& name, const string& password, const Address& OfficeAddress) : User(name, password, OfficeAddress)
{
	//cout << "In constractor of SELLER\n";
}

//---------------------------------------------------------------------------------------------------//

void Seller::save(ofstream& out_file)
{
	User::save(out_file);
	vector<Feedback*>::const_iterator F_itr = f_list.begin();
	vector<Feedback*>::const_iterator F_itrEnd = f_list.end();
	out_file << " " << this->f_list.size();
	for (; F_itr != F_itrEnd; ++F_itr)
	{
		out_file << " " << (*F_itr)->getBuyer().size() << " " << (*F_itr)->getBuyer()
			<< " " << (*F_itr)->getDate().getDay() << " " << (*F_itr)->getDate().getMonth() << " " << (*F_itr)->getDate().getYear()
			<< " " << (*F_itr)->getText().size() << " " << (*F_itr)->getText();


	}
}
//---------------------------------------------------------------------------------------------------//
Seller::~Seller()
{
	//cout << "In desractor of SELLER\n";

	vector<Product*>::iterator P_itr = p_list.begin();
	vector<Product*>::iterator P_itrEnd = p_list.end();
	vector<Feedback*>::iterator F_itr = f_list.begin();
	vector<Feedback*>::iterator F_itrEnd = f_list.end();

	//Deleting the products list
	for (; P_itr != P_itrEnd; ++P_itr)
		delete(*P_itr);

	//deleting the feedback list
	for (; F_itr != F_itrEnd; ++F_itr)
		delete(*F_itr);

	p_list.clear();
	f_list.clear();

}
//---------------------------------------------------------------------------------------------------//
vector<Product*> Seller::getAllProducts() const { return  p_list; }
//---------------------------------------------------------------------------------------------------//
vector<Feedback*> Seller::getAllFeedbacks() const { return f_list; }
//---------------------------------------------------------------------------------------------------//
bool Seller::addNewProductforList(Product* p_data)
{
	//The function add  new Product to the products list
	p_list.push_back(p_data);
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Seller::addNewFeedbackforList(Feedback* f_data)
{
	//The function add new feedback to the Feedback list
	f_list.push_back(f_data);
	return true;
}
//---------------------------------------------------------------------------------------------------//
Product* Seller::findCertainProductInList(const int sir_num) const
{
	//The function find a certain product by comparing the serial number
	//if the product found in the products list of the seller- return product*
	//else return nullptr
	vector<Product*>::const_iterator P_itr = p_list.begin();
	vector<Product*>::const_iterator P_itrEnd = p_list.end();

	for (; P_itr != P_itrEnd; ++P_itr)
		if ((*P_itr)->getSerialNumber() == sir_num)
			return (*P_itr);

	return nullptr;
}
//---------------------------------------------------------------------------------------------------//
int Seller::AmountOfProductList() const { return (int)p_list.size(); }
//---------------------------------------------------------------------------------------------------//
int Seller::AmountOfFeedback() const { return (int)f_list.size(); }
//---------------------------------------------------------------------------------------------------/
void Seller::printProductList() const
{
	cout << "======THE PRODUCTS LIST OF " << this->name << "======\n";
	vector<Product*>::const_iterator P_itr = p_list.begin();
	vector<Product*>::const_iterator P_itrEnd = p_list.end(); \
		int idx = 0;
	for (; P_itr != P_itrEnd; ++P_itr)
	{
		cout << (idx + 1) << ") ";
		(*P_itr)->print();
		cout << endl;
	}
}
//---------------------------------------------------------------------------------------------------//
void Seller::printFeedbackList() const
{
	cout << "======THE FEEDBACKS LIST OF " << this->name << "======\n";
	vector<Feedback*>::const_iterator F_itr = f_list.begin();
	vector<Feedback*>::const_iterator F_itrEnd = f_list.end();
	int idx = 0;
	for (; F_itr != F_itrEnd; ++F_itr)
	{
		cout << (idx + 1) << ") ";
		(*F_itr)->print();
		cout << endl;
	}
}
//---------------------------------------------------------------------------------------------------//
void Seller::show() const
{
	User::show();
	cout << " | Products: " << this->AmountOfProductList() << " items." << endl;
	cout << " | Feedbacks: " << this->AmountOfFeedback() << " feedback." << endl;
}
//---------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const Seller& obj)
{
	os << "UserName: " << obj.name << " | Address: " << obj.address
		<< " | Products: " << obj.AmountOfProductList() << " items. | Feedbacks: " << obj.AmountOfFeedback() << " feedbacks. ";
	return os;
}

istream& operator>>(istream& in, Seller& user)
{
	if (typeid(in) == typeid(ifstream))
	{
		int feedlen;
		string buyerName, text;
		int day, year, month;
		int len;
		in >> feedlen;
		for (int i = 0; i < feedlen; i++)
		{
			in >> len;
			user.getStrFromFile(in, buyerName, len);
			in >> day >> month >> year;
			in >> len;
			user.getStrFromFile(in, text, len);
			user.f_list.push_back(new Feedback(text, buyerName, Date(day, month, year)));
		}
	}
	return in;
}
//---------------------------------------------------------------------------------------------------//