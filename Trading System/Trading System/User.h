#ifndef _USER_H
#define _USER_H

#include "address.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class User
{
public:
	static const int MIN_LEN_PASSWORD = 8;
	static const int MAX_LEN = 21;

protected:
	char name[MAX_LEN];
	char password[MAX_LEN];
	Address address;

public:  //Constractur, Move, Destractor
	User(const char* name, const char* password, const Address& address);
	User(const User& user) = delete; 
	User(User&& other); 
	virtual ~User(); 

public:  //Class Public Methods
	const char* getName() const;
	const Address& getAddress() const;
	virtual void save(ofstream& out_file);

protected: //Class Protected Methods
	bool setAddress(const Address& address);
	bool setName(const char* name);
	bool setPassword(const char* password);
	Address& getAddress();
	const char* getPassword() const;
	virtual void show() const = 0; //obstarction 
};




#endif // _USER_H