#ifndef _FEEDBACK_H
#define _FEEDBACK_H

#include <iostream>
#include <string.h>
#include "Buyer.h"
#include "Date.h"
#pragma warning(disable : 4996)

class Buyer;
class Date;

class Feedback
{
public:
	static constexpr int MAX_LEN_TEXT = 501;

private: //Class variables
	string  text;
	const string buyer;
	const Date 	date;

public: ///Constractur
	Feedback(const string& text, const Buyer* buyer, const Date date);
	Feedback(const string& text, const string& buyer, const Date date); //For loading Feedback from file
	Feedback(const Feedback& other) = delete;


private://Class Private Methods
	void setText(const string& text);

public: //Class Public Methods
	const string& getText() const;
	const string& getBuyer() const;
	const Date& getDate() const;
	void print() const;

};
#endif