#ifndef __DATE_H
#define __DATE_H

#include <string.h>
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;

class Date
{
private:
	int Day;
	int Month;
	int Year;

public: //Constractur
	Date(int day = 1, int month = 1, int year = 2020); //CTOR

private: //Class Private Methods
	bool setDay(const int day);
	bool setMonth(const int month);
	bool setYear(const int year);

public: //Class Public Methods
	int getDay()  const;
	int getMonth() const;
	int getYear() const;
	void show() const;
};
#endif // __DATE_H