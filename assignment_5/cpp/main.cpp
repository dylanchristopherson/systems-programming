#include <string>

#include <iostream>
#include <fstream>


using namespace std;

class Customer {
	public:
		string id;
		double balance;
	
		Customer(string ID, double BALANCE) {
			id = ID;
			balance = BALANCE;
		} 

		string getID() {
			return id;
		}

		double getBalance() {
			return balance;
		}
			
};

int main () {

	int time = 0;
	cout << "Hello world\n";

	Customer john("JOHNNY", 10000.0);

	cout << "John id: " << john.getID() << endl;
	cout << "John balance: " << john.getBalance() << endl;

	// Create Arraylist of customers

	// Create scanner file

	// While infile.hasnext()
		// Check java project for more info


	// Start clock (Check other cpp projects)



	// End clock (check other cpp projects)

	cout << "Program has finished with time of: " << time << endl;


}

