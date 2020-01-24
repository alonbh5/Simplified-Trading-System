#include "Date.h"

Date::Date(int day, int month, int year)
{
	//std::cout << "in c'tor Day " << day << "/" << month << "/" << year << std::endl;
	setDay(day);
	setMonth(month);
	setYear(year);
}
//---------------------------------------------------------------------------------------------------//
bool Date::setDay(const int day)
{
	//set day - if input is not 1-31 range  - puts 1
	if (day < 1 || day > 31)
	{
		cout << "Day should be in 1-31 Range, Value reset to defult day: 1" << endl;
		this->Day = 1;
		return false;
	}
	this->Day = day;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Date::setMonth(const int month)
{
	//set month - if input is not 1-31 range  - puts 1
	if (month < 1 || month > 12)
	{
		cout << "Month should be in 1-12 Range, Value change to defult month: 1" << endl;
		this->Month = 1;
		return false;
	}

	this->Month = month;
	return true;
}
//---------------------------------------------------------------------------------------------------//
bool Date::setYear(const int year)
{
	//set year - if input is not 1-31 range  - puts 2020
	if (year < 2020 || year > 2100)
	{
		cout << "Unvalid year, Value change to defult year: 2020" << endl;
		this->Year = 2020;
		return false;
	}

	this->Year = year;
	return true;
}
//---------------------------------------------------------------------------------------------------//
int Date::getDay()  const { return Day; }
//---------------------------------------------------------------------------------------------------//
int Date::getMonth() const { return Month; }
//---------------------------------------------------------------------------------------------------//
int Date::getYear() const { return Year; }
//---------------------------------------------------------------------------------------------------//
void Date::show() const
{
	//print the date
	cout << Day << "/" << Month << "/" << Year;
}