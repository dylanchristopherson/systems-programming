#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <omp.h>
#include <stdlib.h>

using namespace std;
using namespace std::chrono;

// void sequential(vector<Customer> cl);
// void parallel(vector<Customer> cl);

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

int main() {
	cout << "Beginning program\n";

	vector<Customer> custList;
	
	Customer john("JOHNNY", 10000.0);

	ifstream inFile;
	inFile.open("accounts.txt");

	if (!inFile) {
		cerr << "Unable to open file accounts.txt" << endl;
		exit(1);
	}

	string id;
	double balance;
	int count = 0;
	while (inFile >> id) {
		inFile >> balance;
		custList.push_back(Customer(id, balance));
		count++;
	}

	inFile.close();

	int length = custList.size();

/*************** Sequential Run *******************/
	
	
	cout << "Beginning clock for parallel calculations\n";
	auto start = high_resolution_clock::now();

	int thousandCount = 0;

	for (int i = 0; i < length; i++) {
		if (custList[i].getBalance() < 1000) {
			++thousandCount;
		}
	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Number of accounts with less than $1000 is: " << thousandCount << endl;
	cout << "Sequential program has finished with time of: " << duration.count() << " milliseconds" << endl;

	

/*************** Parallel Run *******************/
	
	cout << "Beginning clock for parallel calculations\n";
	auto start2 = high_resolution_clock::now();


    thousandCount = 0;

	// omp_set_num_threads(4);
// #pragma omp parallel
	#pragma omp for reduction (+:thousandCount)
	for (int i = 0; i < custList.size(); i++) {
		if (custList[i].getBalance() < 1000) {
			thousandCount += 1;
		}
	}

	auto stop2 = high_resolution_clock::now();

	auto duration2 = duration_cast<milliseconds>(stop2 - start2);
	// auto duration = duration_cast<microseconds>(stop - start);

	cout << "Number of accounts with less than $1000 is: " << thousandCount << endl;
	cout << "Parallel program has finished with time of: " << duration2.count() << " milliseconds" << endl;
	
}
