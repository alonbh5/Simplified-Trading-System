#include "Feedback.h"

//---------------------------------------------------------------------------------------------------//
Feedback::Feedback(const char * text,const Buyer * buyer,const Date * date):buyer(buyer), date(date)
{
	//cout << "In ctor Feedback\n" << endl;
	setText(text);
}
//---------------------------------------------------------------------------------------------------//
void Feedback::setText(const char* text)
{
	//The function check the input and set the Text
	if (strlen(text) >= MAX_LEN_TEXT)
	{
		cout << "The name must contain " << (MAX_LEN_TEXT - 1) << " letters or less." << endl;
		return;
	}
	strcpy(this->text, text);
}
//---------------------------------------------------------------------------------------------------//
const Buyer* Feedback::getBuyer() const {return buyer;}
//-------------------------------------------------------------------//
const Date * Feedback::getDate() const{return date;}
//-------------------------------------------------------------------//
void Feedback::print() const
{
	cout << "The feedback: " << text;
	cout << " | Date of Feedback : ";
	date->show();
	cout << " |Name of buyer: " << buyer->getName();
}
