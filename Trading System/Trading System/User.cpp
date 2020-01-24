#include "User.h"


User::User(const string& name, const string& password, const Address& address) :address(address)
{
	setName(name);
	setPassword(password);
}
//-------------------------------------------------------------------//

User::User(ifstream& inFile) : address()
{
	inFile >> *this;
	inFile >> (this->address);

}
//-------------------------------------------------------------------//

User::~User()
{
}
//-------------------------------------------------------------------//
bool User::setName(const string& name)
{
	//The function check input and set name
	int x = (int)name.size();
	if (x >= MAX_LEN)
	{
		cout << "The name must contain " << (MAX_LEN - 1) << " letters or less." << endl;
		return false;
	}
	this->name = name;
	return true;
}
//-------------------------------------------------------------------//
bool User::setPassword(const string& password)
{
	//The function check input and set password

	if (password.size() < MIN_LEN_PASSWORD)
	{
		cout << "Your Password is too short\n";
		return false;
	}
	if (password.size() > MAX_LEN)
	{
		cout << "Your Password is too long\n";
		return false;
	}
	this->password = password;
	return true;
}
//-------------------------------------------------------------------//
const string& User::getName() const { return name; }
//---------------------------------------------------------------------------------------------------//
const string& User::getPassword() const { return password; }
//---------------------------------------------------------------------------------------------------//
const Address& User::getAddress() const { return address; }

bool User::setAddress(const Address& address)
{
	this->address = address;
	return true;
}
//---------------------------------------------------------------------------------------------------//
Address& User::getAddress() { return address; }
//---------------------------------------------------------------------------------------------------//
void User::show() const
{
	cout << "Username: " << name << " | Office Address: ";
	this->address.show();

}
//---------------------------------------------------------------------------------------------------//

void User::save(ofstream& out_file)
{
	char delimter = ' ';
	out_file << this->name.size() << delimter << this->name << delimter << this->password.size() << delimter << this->password << delimter << this->address;

}
//-------------------------------------------------------------------//

istream& operator>>(istream& in, User& user)
{
	if (typeid(in) == typeid(ifstream))
	{
		int len;
		in >> len;
		user.getStrFromFile(in, user.name, len);
		in >> len;
		user.getStrFromFile(in, user.password, len);

	}
	return in;
}

//-------------------------------------------------------------------//

void User::getStrFromFile(istream& in, string& str, int len)
{
	in.get();
	int i;
	for (i = 0; i < len; i++)
		str.insert(str.end(), in.get());
}