#include <string>

#include <iostream>
#include <fstream>


using namespace std;

class Customer {
	public:
		string id;
		double balance;
	
		Customer() {
			id = "";
			balance = 0.0;
		}

		Customer(string ID, double BALANCE) {
			id = ID;
			balance = BALANCE;
		} 

		void setID(string ID) {
			id = ID;
		}

		void setBalance(double BALANCE) {
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

	// There are 8000000 lines in the file, that means there
	// are 4000000 customers

	Customer custList[4000];

	int time = 0;
	cout << "Hello world\n";

	Customer john("JOHNNY", 10000.0);

	cout << "John id: " << john.getID() << endl;
	cout << "John balance: " << john.getBalance() << endl;

	ifstream inFile;
	inFile.open("./accounts.txt");

	if (!inFile) {
		cerr << "Unable to open file accounts.txt" << endl;
		exit(1);
	}
/*
	string line;
	int number_of_lines;
	while (std::getline(inFile, line))
	        ++number_of_lines;
	std::cout << "Number of lines in text file: " << number_of_lines;
*/

	string id;
	double balance;
	int count = 0;
	while (inFile >> id) {
		inFile >> balance;
		cout << "id: " << id << endl;
		cout << "balance: " << balance << endl;  

		custList[count].setID(id);
		custList[count].setBalance(balance);
		count ++;

	} 

	// custList[0].setID("TEST");
	// custList[0].setBalance(100);

	// Create Arraylist of customers

	// Create scanner file

	// While infile.hasnext()
		// Check java project for more info


	// Start clock (Check other cpp projects)



	// End clock (check other cpp projects)

	cout << "Program has finished with time of: " << time << endl;


}

