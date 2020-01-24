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
	string name;
	string password;
	Address address;

public:  //Constractur, Move, Destractor
	User(ifstream& inFile);
	User(const string& name, const string& password, const Address& address);
	User(const User& user) = delete;
	virtual ~User();

public:  //Class Public Methods
	const string& getName() const;
	const Address& getAddress() const;
	virtual void save(ofstream& out_file);

protected: //Class Protected Methods
	friend istream& operator>>(istream& inFile, User& user);
	bool setAddress(const Address& address);
	bool setName(const string& name);
	bool setPassword(const string& password);
	Address& getAddress();
	const string& getPassword() const;
	virtual void show() const = 0; //obstarction 
	void getStrFromFile(istream& in, string& str, int len);  // Helper for loading file

};

#endif // _USER_H