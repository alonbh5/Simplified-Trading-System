#ifndef _Megauser_H
#define _Megauser_H

#include "Buyer.h"
#include "seller.h"
#include <fstream>

class Megauser :public Seller, public Buyer
{
public://Constractur, Move, Destractor 
	Megauser(ifstream& in);
	Megauser(const string& name, const string& password, const Address& address);
	Megauser(const Megauser& other) = delete;
	virtual ~Megauser();

	//Class Public Methods
	virtual void show() const;
	friend ostream& operator<<(ostream& os, const Megauser& obj);
	virtual void save(ofstream& out_file);
};
#endif // !_Megauser_H