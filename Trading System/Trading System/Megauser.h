#ifndef _Megauser_H
#define _Megauser_H

#include "Buyer.h"
#include "seller.h"
class Megauser :public Seller, public Buyer
{
public://Constractur, Move, Destractor 
	Megauser(const char*name,const char* password, const Address& address);
	Megauser(const Megauser& other) = delete;
	Megauser(Megauser&& other);
	virtual ~Megauser();

	//Class Public Methods
	virtual void show() const;
	friend ostream& operator<<(ostream& os, const Megauser& obj);
	virtual void save(ofstream& out_file);
};
#endif // !_Megauser_H
