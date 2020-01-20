#include "User.h"

User::User(const char* name, const char* password, const Address& address):address(address)
{
	setName(name);
	setPassword(password);
}

//-------------------------------------------------------------------//
User::User(User&& other):address(other.address)
{
	setName(other.name);
	setPassword(other.password);
}
//-------------------------------------------------------------------//
User::~User()
{
}
//-------------------------------------------------------------------//
bool User::setName(const char* name)
{
	//The function check input and set name
	int x = (int)strlen(name);
	if (x >= MAX_LEN)
	{
		cout << "The name must contain " << (MAX_LEN - 1) << " letters or less." << endl;
		return false;
	}
	strcpy(this->name, name);
	return true;
}
//-------------------------------------------------------------------//
bool User::setPassword(const char* password)
{
	//The function check input and set password

	if (strlen(password) < MIN_LEN_PASSWORD)
	{
		cout << "Your Password is too short\n";
		return false;
	}
	strcpy(this->password, password);
	return true;
}
//-------------------------------------------------------------------//
const char* User::getName() const { return name; }
//---------------------------------------------------------------------------------------------------//
const char* User::getPassword() const { return password; }
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
	 out_file << strlen(this->name) << delimter << this->name << delimter << strlen(this->password) << delimter << this->password << delimter << this->address;
 }


