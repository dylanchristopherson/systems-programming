#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

using namespace std;

int main() {
	// Part 1
	size_t Maxsize = 80;	
	char Readbuffer[80];


	getcwd(Readbuffer, Maxsize);

	cout << Readbuffer << endl;

	// Part 2
	vector<string> v;

	v.push_back("Test");
	v.push_back("Hello again");
	v.push_back("what's up");
	v.push_back("asdfhahsdf");

	string hist;
	cout << "How much history would you like to see?";
	getline(cin, hist);

	cout << "Hist: " << hist << endl;
	//for (int i = 0; i < hist; i++) {
	//	cout << "Vector: " << v[i] << endl;
	//}

	return(0);
}
