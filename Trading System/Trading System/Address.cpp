#include "Address.h"

//---------------------------------------------------------------------------------------------------//
Address::Address(const string& street, const int houseNumber, const string& city, const string& country, const int zipcode)
{
	//cout << "in c'tor Address" << endl;
	setNumber(houseNumber);
	setCity(city);
	setStreet(street);
	setCountry(country);
	setZipcode(zipcode);
}
//---------------------------------------------------------------------------------------------------//
bool Address::setStreet(const string& street)
{
	//set a Street - if not good reset to "Bad input"
	int x;
	x = (int)street.size();

	if (x > MAX_STR_LENGTH)
	{
		cout << "Street cant be longer then " << MAX_STR_LENGTH - 1 << endl;
		Street = "Bad input";
		return false;
	}

	Street = street;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Address::setCity(const string& city)
{
	//set a city - if not good reset to "Bad input"
	int x;
	x = city.size();

	if (x > MAX_STR_LENGTH)
	{
		cout << "City cant be longer then " << MAX_STR_LENGTH << endl;
		City = "Bad input";
		return false;
	}

	City = city;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Address::setNumber(const int houseNumber)
{ //set a house Number - if not good reset to -1

	if (houseNumber < 1 || houseNumber >9999)
	{
		cout << "House Number should be in 1-9999 Range, Value didn't changed" << endl;
		this->houseNumber = -1;
		return false;
	}
	this->houseNumber = houseNumber;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Address::setZipcode(const int Zipcode)
{
	//set a Zipcode - if not good reset to -1

	if (Zipcode <= 0)
	{
		cout << " Zip code should be at least 5 number long, Value didn't changed" << endl;
		this->Zipcode = -1;
		return false;
	}
	this->Zipcode = Zipcode;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Address::setCountry(const string& country)
{
	//set a Country - if not good reset to "Bad input"

	int x;
	x = Country.size();

	if (x > MAX_STR_LENGTH)
	{
		cout << "Country cant be longer then " << MAX_STR_LENGTH - 1 << endl;
		Country = "Bad input";
		return false;
	}

	Country = country;
	return true;

}
//---------------------------------------------------------------------------------------------------//
const string& Address::getStreet() const { return Street; }
//---------------------------------------------------------------------------------------------------//
const string& Address::getCity()   const { return City; }
//---------------------------------------------------------------------------------------------------//
const string& Address::getCountry()   const { return Country; }
//---------------------------------------------------------------------------------------------------//
int Address::getNumber()         const { return houseNumber; }
//---------------------------------------------------------------------------------------------------//
int Address::getZipcode()         const { return Zipcode; }
//---------------------------------------------------------------------------------------------------//
void Address::show() const
{
	//print the address on screen
	cout << houseNumber << " " << Street << ".st " << City << ", " << Country << " - " << Zipcode << ".";
}
//---------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const Address& obj)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << ((int)obj.Street.size()) << " " << obj.Street << " " << obj.houseNumber << " " << ((int)obj.City.size()) << " " << obj.City << " " << ((int)(obj.Country.size())) << " " << obj.Country << " " << obj.Zipcode;
	}
	else
	{
		os << obj.houseNumber << " " << obj.Street << ".st " <<
			obj.City << ", " << obj.Country << " - " << obj.Zipcode << ".";
	}
	return os;
}
//---------------------------------------------------------------------------------------------------//
istream& operator>>(istream& in, Address& obj)
{
	if (typeid(in) == typeid(ifstream))
	{
		int len;

		in >> len;
		obj.getStrFromFile(in, obj.Street, len);
		in >> obj.houseNumber;
		in >> len;
		obj.getStrFromFile(in, obj.City, len);
		in >> len;
		obj.getStrFromFile(in, obj.Country, len);
		in >> obj.Zipcode;

	}
	return in;
}
//---------------------------------------------------------------------------------------------------//
void Address::getStrFromFile(istream& in, string& str, int len)
{
	in.get();
	int i;
	for (i = 0; i < len; i++)
		str.insert(str.end(), in.get());
}
//---------------------------------------------------------------------------------------------------//