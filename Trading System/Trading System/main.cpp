#include "System.h"
#include "Inputs.h"


int main()
{
	cout << "============================ WELCOME TO OUR SYSTEM ============================" <<endl;
	System sys;
	sys.LoadUsers("Best_System.txt");
	RunSystem(sys);
	sys.SaveUsers("Best_System.txt");
	cout<<"Thank You!!\n";
	cout<<"============================    SEE YOU AGAIN, Alon & Yair    ===========================\n";	
}
