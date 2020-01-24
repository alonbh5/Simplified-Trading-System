#include "Feedback.h"

//---------------------------------------------------------------------------------------------------//
Feedback::Feedback(const string& text, const Buyer* buyer, const Date date) :buyer(buyer->getName()), date(date)
{
	//cout << "In ctor Feedback\n" << endl;

	setText(text);
}
//---------------------------------------------------------------------------------------------------//

Feedback::Feedback(const string& text, const string& buyer, const Date date) : date(date), buyer(buyer)
{
	this->text = text;
}

//---------------------------------------------------------------------------------------------------//
void Feedback::setText(const string& text)
{
	//The function check the input and set the Text
	if (text.size() >= MAX_LEN_TEXT)
	{
		cout << "The name must contain " << (MAX_LEN_TEXT - 1) << " letters or less." << endl;
		return;
	}
	this->text = text;
}
//---------------------------------------------------------------------------------------------------//

const string& Feedback::getText() const
{
	return text;
}
//---------------------------------------------------------------------------------------------------//
const string& Feedback::getBuyer() const { return buyer; }
//-------------------------------------------------------------------//
const Date& Feedback::getDate() const { return date; }
//-------------------------------------------------------------------//
void Feedback::print() const
{
	cout << "The feedback: " << text;
	cout << " | Date of Feedback : ";
	date.show();
	cout << " |Name of buyer: " << buyer;
}
//---------------------------------------------------------------------------------------------------//


