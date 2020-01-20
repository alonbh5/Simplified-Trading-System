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
	char  text[MAX_LEN_TEXT];
	const Buyer* const	buyer;
	const Date*  const	date;

public: ///Constractur
	Feedback(const char* text,const Buyer* buyer, const Date* date);
	Feedback(const Feedback &other) = delete;

private://Class Private Methods
	void setText(const char* text);

public: //Class Public Methods
	const Buyer* getBuyer() const;
	const Date* getDate() const;
	void print() const;
};
#endif
