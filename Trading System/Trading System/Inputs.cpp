#include "Inputs.h"

void RunSystem(System& sys)
{
	//Main function for geting inputs from user 
	bool runTheSystem = true;
	bool flag = true;
	int digit;

	while (runTheSystem) //until user Type 11-Exit
	{
 		printMenuAndInputDigit(digit);
 		openFunction(digit,sys, runTheSystem);
	}
}
//---------------------------------------------------------------------------------------------------//
void printMenuAndInputDigit(int& digit)
{
	//void function for printing the menu
		bool flag = false;
		cout << "\n\n=================MENU================\n";
		std::cout << "please Type the relevant number from the following MENU:\n";
		std::cout << "1- Adding a Seller\n";
		std::cout << "2- Adding a Buyer\n";
		std::cout << "3- Adding a Megauser\n";
		std::cout << "4- Adding a Product To Seller or Megauser's Products List\n";
		std::cout << "5- Adding a Feedback To Seller or Megauser's Feedback List\n";
		std::cout << "6- Adding a Product To Buyer or Megauser's Wishlist \n";
		std::cout << "7- Create a New Order For a Certain Buyer or Megauser\n";
		std::cout << "8- Pay for a ceratin Order\n";
		std::cout << "9- Show ONLY the Buyers Deatils In System\n";
		std::cout << "10- Show ONLY the Sellers Deatils In System\n";
		std::cout << "11- Show ONLY the MegaUsers Deatils In System\n";
		std::cout << "12- Show all Products That Goes By a Ceartin Name\n";
		std::cout << "13- Tests For The Operators\n";
		std::cout << "14- EXIT\n";

		while (!flag)
		{
			cout << "Type A number: ";
			cin >> digit;			
			flag = IsAgoodDigit(digit);
		}
		
}
//---------------------------------------------------------------------------------------------------//
static void openFunction(int& digit, System& sys, bool& runTheSystem)
{
	//function that open the currect function by the digit
	cout << endl << endl;
	switch (digit)
	{
	case 1:
	{
		addSeller(sys);
		break;
	}
	case 2:
	{
		addBuyer(sys);
		break;
	}
	case 3:
	{
		addMegaUser(sys);
		break;
	}
	case 4:
	{
		addProductToSeller(sys);
		break;
	}
	case 5:
	{
		addFeedbackToSeller(sys);
		break;
	}
	case 6:
	{
		addProductToWishList(sys);
		break;
	}
	case 7:
	{
		orderList(sys);
		break;
	}
	case 8:
	{
		payOrder(sys);
		break;
	}
	case 9:
	{
		PrintTheBuyerList(sys);
		break;
	}
	case 10:
	{
		printTheSellerList(sys);
		break;
	}
	case 11:
	{
		PrintTheMegaUserList(sys);
		break;
	}
	case 12:
	{
		showAllProductByName(sys);
		break;
	}
	case 13:
	{
		testForTheOperators(sys);
		break;
	}

	case 14:
	{	
		runTheSystem = false;
		break;
	}
	}
}
//---------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------//
//MENU - 1 FUNCTION
static void addSeller(System& sys)
{
	//The function get input from user and creating a new seller
	//by using the currect function in system
	char name[User::MAX_LEN];
	char password[User::MAX_LEN];
	inputForCreatingNewUser(sys, "Seller", name, password);
	Address address = getAddressFromUser();
	sys.addSeller(name, password, address,true);
}
//---------------------------------------------------------------------------------------------------//
//MENU - 2 FUNCTION
static void addBuyer(System& sys)
{
	//The function get input from user and creating a new buyer
	//by using the currect function in system
	char name[User::MAX_LEN];
	char password[User::MAX_LEN];
	inputForCreatingNewUser(sys, "Buyer", name, password);
	Address address = getAddressFromUser();
	sys.addBuyer(name, password, address,true);
}
//---------------------------------------------------------------------------------------------------//
//MENU - 3 FUNCTION
void addMegaUser(System& sys)
{
	char name[User::MAX_LEN];
	char password[User::MAX_LEN];
	inputForCreatingNewUser(sys, "MegaUser", name, password);
	Address address = getAddressFromUser();
	sys.addMegaUser(name, password, address,true);
}
//---------------------------------------------------------------------------------------------------//
//MENU - 4 FUNCTION
static void addProductToSeller(System &sys)
{
	//The function get input from user and creating a new product for a certain seller
	//if seller dosent exist - exit and cout a message to the user
	char Product_name[Product::MAX_LEN_NAME];
	char Seller_name[User::MAX_LEN];
	double price; 
	int category;
	bool flag = false;

	cout << "\n====== Adding A Product To Seller ======\n";
	cin.ignore();
	cout << "Type the Name of the new product:\n";
	cin.getline(Product_name, Product::MAX_LEN_NAME);
	while (!flag) // checking the input
	{
		cout << "Type the Category of " << Product_name << " :\n" << "1-KIDS, 2-ELECTRICAL, 3-OFFICE, 4-CLOTHING\n";
		cin >> category;
		flag = IsCategory(category);
		if (!flag)
			cout << "Not a number of category\n";
	}
	cout << "Type the Price of the Product " << Product_name << endl;
	cin >> price;
	while (price < 0)
	{
		cout << "Price should be a positive number\n";
		cin >> price;
	}
	cout << "Type the name of the Seller you want add a product\n";
	cin.ignore();
	cin.getline(Seller_name, User::MAX_LEN);

	sys.addProductToSeller(Seller_name, Product_name, price, category);
}
//---------------------------------------------------------------------------------------------------//
//MENU - 5 FUNCTION
void addFeedbackToSeller(System & sys)
{
	//The function creating a new feedback ONLY if the buyer buy product from seller
	//This function will get the input from user and using the appropriate System function
	char buyerName[User::MAX_LEN];
	char sellerName[User::MIN_LEN_PASSWORD];
	char text[Feedback::MAX_LEN_TEXT];;
	int day, month, year;

	cout << "\n====== Add Feedback To Seller ======\n";
	cout << "please Type the name of the buyer\n";
	cin.ignore();
	cin.getline(buyerName, User::MAX_LEN);
	cout << "please Type the name of the seller you want to write him a Feedback\n";
	cin.getline(sellerName, User::MAX_LEN);

	cout << "please write the Date of Feedback\n";
	getInputDate(day, month, year);

	cin.ignore();
	cout << "Please Write your Feedback up to 500 letters\n"; 
	cin.getline(text, Feedback::MAX_LEN_TEXT);

	sys.addFeedbackToSeller(buyerName, sellerName, day, month, year, text);
}
//---------------------------------------------------------------------------------------------------//
//MENU - 6 FUNCTION
void addProductToWishList(System & sys) 
{
	//The function puts products to the wishlist's buyer.
	//This function will get the input from user and using the appropriate System function
	int serial;
	char BuyerName[User::MAX_LEN];
	char ProductName[Product::MAX_LEN_NAME];

	cout << "\n====== Adding A Product To Wishlist ======\n";
	cin.ignore();
	cout << "please Type the name of the product you want to add\n";
	cin.getline(ProductName, Product::MAX_LEN_NAME);
	
	//this function will print ONLY the available product by "ProductName"
	if (!sys.showProductByName(ProductName, "Available"))
		return;

	cout << "Please Type the Serial of the product you wish to add: ";
	cin >> serial;

	cout << endl;
	cout << "Please Type the Name of the buyer\n";
	cin.ignore();
	cin.getline(BuyerName, User::MAX_LEN);

	sys.addProductToWishList(BuyerName, serial);
}
//---------------------------------------------------------------------------------------------------//
//MENU - 7 FUNCTION
void orderList(System & sys)
{ 
	//The function will make order list by getting input from the user.
	//User can add few products to a certain order
	char BuyerName[User::MAX_LEN];
	Buyer* buyer;
	Order* order;
	cout << "\n====== Creating a new order ======\n";
	cout << "Please Type the Name of the buyer you wish to make an order for \n";
	cin.ignore();
	cin.getline(BuyerName, User::MAX_LEN);
	
	order = sys.OpenNewOrderList(BuyerName, &buyer); //open new order
	if (order)
	{
		if (buyer->PrintWishlist())
			getSerialNumberAndAddProductToOrder(buyer, order, sys);


		if (order->getLogsize_orderlist() == 0)
		{
			cout << "Cant make empty Order -Order deleted!" << endl;
			sys.DeleteLastOrder(buyer);
		}
	}
}

//---------------------------------------------------------------------------------------------------//
//MENU - 8 FUNCTION
void payOrder(System & sys) 
{
	int count = 0;
	int serial;
	bool flag = true;
	char BuyerName[User::MAX_LEN];
	Buyer* buyer;

	cout << "\n====== Paying for an Order ======\n";
	cout << "Please Type the Name of the buyer you wish to complete one of its order \n";
	cin.ignore();
	cin.getline(BuyerName, User::MAX_LEN);

	buyer = sys.buyerIsExist(BuyerName);
	if (!buyer) 
	{
		cout << BuyerName << " does not exist!" << endl;
		return;
	}
	count= buyer->printOrderNotpaid();
	if (count == 0) //no order to pay
	{
		cout << "No order that not paid\n";
		return;
	}
	cout << "Type Order Number to pay" << endl;
	cin >> serial;

	sys.payOrder(buyer,serial);
}
//---------------------------------------------------------------------------------------------------//
//MENU - 9 FUNCTION
static void printTheSellerList(const System & sys)  { sys.printTheSellerList(); }
//---------------------------------------------------------------------------------------------------//
//MENU - 10 FUNCTION
static void PrintTheBuyerList(const System & sys)  { sys.PrintTheBuyerList(); }
//---------------------------------------------------------------------------------------------------//
//MENU - 11 FUNCTION
static void PrintTheMegaUserList(const System& sys) { sys.PrintTheMegaUserList(); }

//---------------------------------------------------------------------------------------------------//
//MENU - 12 FUNCTION
static void showAllProductByName(const System & sys) 
{
	char Product_name[Product::MAX_LEN_NAME];

	cout << "\n====== Searching All The Product By Name ======\n";
	cout << "Type The name you want to search\n";
	cin.ignore();
	cin.getline(Product_name, Product::MAX_LEN_NAME);
	sys.showProductByName(Product_name, "All");
}
//---------------------------------------------------------------------------------------------------//
//MENU - 13 FUNCTION
static void testForTheOperators(const System& sys)
{
	cout << "\n====== Test the Different Operators ======\n";
	cout << "1: > (Compare bewtween 2 Buyer's Wishlist Total Price)" << endl;
	cout << "2: += (Add buyer or seller)" << endl;
	cout << "3: << (Print seller buyer and product with cout <<)" << endl;
	cout << "Type The Operators number you want to search\n";
	int num;
	cin >> num;
	//fix ot
	
	switch (num)
	{
	case 1:
	{
		TestOprator1(sys);
		break;
	}
	case 2:
	{
		TestOprator2(sys);
		break;
	}
	case 3:
	{
		TestOprator3(sys);
		break;
	}
	default:
	{
		cout << "Worng input - exit" << endl;
		break;
	}
	}


}


//============================================HELPERS FUNCTION ==============================================//
static void inputForCreatingNewUser(System& sys, const char* str, char* name, char* password)
{
	bool flagPassword = false, flagName = false;;

	cout << "\n====== Adding A " << str << " ======\n";
	cin.ignore();
	while (!flagName) // checking the input
	{
		cout << "Please Type a Username of the " << str << endl;
		cin.getline(name, User::MAX_LEN);
		if (!sys.userIsExist(name))
			flagName = true;
		else
			cout << name << " Is taken - choose a diffent user name " << str << endl;
		cout << endl;

	}
	while (!flagPassword)// checking the input
	{
		cout << "Please Type The Password of " << str << ": " << name << " (Min: 8 characters, Max: 20 characters)\n";
		cin.getline(password, User::MAX_LEN);
		flagPassword = CheckThePassword(password, "seller");
		cout << endl;
	}

	cout << "Please Type The Address of " << str << ": " << name << "\n";

}
//---------------------------------------------------------------------------------------------------//
static void getSerialNumberAndAddProductToOrder(Buyer* buyer,Order *order,System& sys)
{
	bool flag = true;
	int sir = 0;
	int tempWishlistSize = buyer->getLogsize_wishlist();

	while (flag) // until user input 2- NO
	{
		cout << "Choose the Serial number of the product you wish to add : " << endl;
		cin >> sir;
		if (sys.ActivateAddfromBuyer(buyer,sir,order))
			tempWishlistSize--;
		
		// asking the user if want to add another product to the order just if the wishlist isn't empty
		if (tempWishlistSize != 0)
		{
			cout << "do you wish to add another item?\n1) Yes\n2) NO" << endl;
			cin >> sir;	
		}
		if (sir != 1 || tempWishlistSize==0)
			flag = false;

	}
	

}
//---------------------------------------------------------------------------------------------------//
static bool IsAgoodDigit(int & digit)
{
	//The function check if the digit in the right range
	if (digit > 0 && digit <= 14)
		return true;
	else
	{
		cout << "Sorry, Not A Good Number.\nplease Try Again.\n";
		return false;
	}
}
//---------------------------------------------------------------------------------------------------//
static Address getAddressFromUser()
{
	//Helper function for gets and creates an Address object
	char street[Address::MAX_STR_LENGTH];
	char city[Address::MAX_STR_LENGTH];
	char country[Address::MAX_STR_LENGTH];
	int houseNumber;
	int zipCode;

	cout << "Please enter Street, HouseNumber, City, Country, and ZipCode- one by one\n";
	cin.getline(street, Address::MAX_STR_LENGTH);
	cin >> houseNumber;
	cin.ignore();
	cin.getline(city, Address::MAX_STR_LENGTH);
	cin.getline(country, Address::MAX_STR_LENGTH);
	cin >> zipCode;
	return (Address(street, houseNumber, city, country, zipCode));

}
//---------------------------------------------------------------------------------------------------//
static bool CheckThePassword(const char* password, const char* type)
{
	//Helper function for Checking Password for Buyer and Seller
	if (strcmp(type, "seller") == 0) // check seller password
	{
		if (strlen(password) < User::MIN_LEN_PASSWORD)
		{
			cout << "Your Password is Too Short\n";
			return false;
		}
		return true;
	}
	if (strcmp(type, "buyer") == 0) // check buyer function
	{
		if (strlen(password) < User::MIN_LEN_PASSWORD)
		{
			cout << "Your Password is Too Short\n";
			return false;
		}
		return true;
	}
	return false;

}
//---------------------------------------------------------------------------------------------------//
static bool IsUserNameExist(const char* name, const char* type, System& sys)
{
	//Helper function for checking Existed BUYER/SELLER	
	if (strcmp(type, "seller") == 0)
	{
		Seller* seller = sys.sellerIsExist(name);
		if (seller)
		{
			cout << "The seller " << name << " is already exist\n";
				return false;
		}
		return true;
	}
	if (strcmp(type, "buyer") == 0)
	{
		Buyer* buyer = sys.buyerIsExist(name);
		if (buyer)
		{
			cout << "The buyer " << name << " is already exist\n";
			return false;
		}
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------------------//
static void getInputDate(int& day, int& month, int& year)
{

	//Helper funciton that gets inputs for DATE 
	cout << "Day ";
	cin >> day;
	cout << "Month ";
	cin >> month;
	cout << "Year ";
	cin >> year;
	cout << endl;
}
//---------------------------------------------------------------------------------------------------//
static bool IsCategory(int & category)
{
	//Helper function for check a right range of category
	if (category >= 1 && category <= 4)
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------------------------------//
static void TestOprator1(const System& sys)
{
	Buyer* buyer1, * buyer2;
	char str[User::MAX_LEN];

	cout << "Test 1:for If Buyer 1 Total Wishlish Price is Bigger (>) Then Buyer 2 "<<endl;
	cout << "Enter Name of Buyer 1 :";
	cin.ignore();
	cin.getline(str,User::MAX_LEN);
	cout << endl;
	buyer1 = sys.buyerIsExist(str);
	if (buyer1)
	{
		cout << "Enter Name of Buyer 2 :";
		cin.getline(str, User::MAX_LEN);
		cout << endl;
		buyer2 = sys.buyerIsExist(str);
		if (buyer2)
		{
			if (*buyer1 > *buyer2)
			{
				cout << "Buyer1 - " << buyer1->getName() << " Wishlist Price Is Bigger then Buyer 2 - " << buyer2->getName() << endl;
			}
			else
			{
				cout << "Buyer1 - " << buyer1->getName() << " Wishlist Price Is Smaller or Equal to Buyer 2 - " << buyer2->getName() << endl;
			}
		}
		else
		{
			cout << "Sorry Buyer: " << str << " was not found" << endl << "exiting > test" << endl;
		}


	}
	else
	{
		cout << "Sorry Buyer: " << str << " was not found" << endl << "exiting > test"<<endl;
	}

}
//---------------------------------------------------------------------------------------------------//
static void TestOprator2(const System& sys)
{
	cout << "Function 1-3 using the operator += for adding Seller, Buyer or Megauser to System\n";
}
//---------------------------------------------------------------------------------------------------//
static void TestOprator3(const System& sys)
{
	cout << "The following function using the operator <<\n";
	cout << "Function 9: ONLY the SELLERS\n";
	cout << "Function 10: ONLY the BUYER\n";
	cout << "Function 11: ONLY the MegaUser\n";
	cout << "Function 12: show products by name\n";

}
//---------------------------------------------------------------------------------------------------//
