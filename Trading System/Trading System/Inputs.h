#ifndef _INPUTS_H
#define _INPUTS_H

#include <iostream>
#include <string.h>
#include <string>
#include "System.h"
using namespace std;


void RunSystem(System& system);
void printMenuAndInputDigit(int& digit);
static void openFunction(int& digit, System& sys, bool& runTheSystem);

static void addSeller(System& sys);//Function 1
static void addBuyer(System& sys); //Function 2
static void addMegaUser(System& sys);//Function 3
static void addProductToSeller(System& sys);//Function 4
static void addFeedbackToSeller(System& sys);//Function 5
static void addProductToWishList(System& sys); //Function 6
static void orderList(System& sys);//Function 7
static void payOrder(System& sys); //Function 8
static void printTheSellerList(const System& sys); //Function 9
static void PrintTheBuyerList(const System& sys);// Function 10
static void PrintTheMegaUserList(const System& sys);//Function 11
static void showAllProductByName(const System& sys); //Function 12
static void testForTheOperators(const System& sys); //Function 13


//HELPERS
static void inputForCreatingNewUser(System& sys, const string& str, string& name, string& password);
static void getSerialNumberAndAddProductToOrder(Buyer* buyer, Order* order, System& sys);//help to function 7
static bool IsAgoodDigit(int& digit);
static Address getAddressFromUser();
static bool CheckThePassword(const string& password);
static bool IsUserNameExist(const string& name, const string& type, System& sys);
static void getInputDate(int& day, int& month, int& year);
static bool IsCategory(int& category);
static bool CheckAddressStrings(const string& street, const string& city, const string& country);
static void TestOprator1(const System& sys);
static void TestOprator2(const System& sys);
static void TestOprator3(const System& sys);

#endif //_INPUTS_H