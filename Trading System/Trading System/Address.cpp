#include "Address.h"

//---------------------------------------------------------------------------------------------------//
Address::Address(const char* street, const int houseNumber, const char* city, const char* country,const int zipcode)
{
	//cout << "in c'tor Address" << endl;
	setNumber(houseNumber);
	setCity(city);
	setStreet(street);
	setCountry(country);
	setZipcode(zipcode);
}
//---------------------------------------------------------------------------------------------------//
const Address& Address::operator=(const Address& other)
{
	if (this != &other)
	{
		setStreet(other.Street);
		setCity(other.City);
		setCountry(other.Country);
		setNumber(other.houseNumber);
		setZipcode(other.Zipcode);
	}
	return *this;
}
//---------------------------------------------------------------------------------------------------//
const Address& Address::operator=(const Address&& other)
{
	if (this != &other)
	{
		setStreet(other.Street);
		setCity(other.City);
		setCountry(other.Country);
		setNumber(other.houseNumber);
		setZipcode(other.Zipcode);
	}
	return *this;
}
//---------------------------------------------------------------------------------------------------//
ostream& operator<<(ostream& os, const Address& obj)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << strlen(obj.Street) << " " << obj.Street << " " << obj.houseNumber << " " << strlen(obj.City) << " " << obj.City << " " << strlen(obj.Country) << " " << obj.Country << " " << obj.Zipcode;
	}
	else
	{
		os << obj.houseNumber << " " << obj.Street << ".st " <<
			obj.City << ", " << obj.Country << " - " << obj.Zipcode << ".";
	}
	return os;
}
//---------------------------------------------------------------------------------------------------//
bool Address::setStreet(const char* street)
{
	//set a Street - if not good reset to "Bad input"
	int x;
	x = (int)strlen(street);

	if (x > MAX_STR_LENGTH)
	{
		cout << "Street cant be longer then " << MAX_STR_LENGTH - 1 << endl;
		strcpy(this->Street, "Bad input");
		return false;
	}

	strcpy(this->Street, street);
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Address::setCity(const char* city)
{
	//set a city - if not good reset to "Bad input"
	int x;
	x = (int)strlen(city);

	if (x > MAX_STR_LENGTH)
	{
		cout << "City cant be longer then " << MAX_STR_LENGTH << endl;
		strcpy(this->City, "Bad input");
		return false;
	}

	strcpy(this->City, city);
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
bool Address::setCountry(const char* Country)
{
	//set a Country - if not good reset to "Bad input"

	int x;
	x = (int)strlen(Country);

	if (x > MAX_STR_LENGTH)
	{
		cout << "Country cant be longer then " << MAX_STR_LENGTH -1 << endl;
		strcpy(this->Country, "Bad input");
		return false;
	}

	strcpy(this->Country, Country);
	return true;

}
//---------------------------------------------------------------------------------------------------//
const char* Address::getStreet() const {return Street;}
//---------------------------------------------------------------------------------------------------//
const char* Address::getCity()   const {return City;}
//---------------------------------------------------------------------------------------------------//
const char* Address::getCountry()   const {return Country; }
//---------------------------------------------------------------------------------------------------//
int Address::getNumber()         const{return houseNumber;}
//---------------------------------------------------------------------------------------------------//
int Address::getZipcode()         const{return Zipcode;}
//---------------------------------------------------------------------------------------------------//
void Address::show() const
{
	//print the address on screen
	cout << houseNumber << " " << Street << ".st " << City << ", " << Country << " - " << Zipcode << ".";
}
