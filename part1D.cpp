#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

using namespace std;

void getPwd() {
	// Part 1
	size_t Maxsize = 80;	
	char Readbuffer[80];

	getcwd(Readbuffer, Maxsize);

	cout << Readbuffer << endl;
}

void getHistory(vector<string> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << i+1 << " " << v[i] << endl; 
	}
}

int main() {

	string str;
	cout << "The command line shout repeat now\n";

	vector<string> v;

	char * cstr;
	char * pch;
	char *C;

	while(1) {
		getline(cin,str);

		cstr = new char [str.length()+1];
		strcpy(cstr, str.c_str());

		string a;
	        pch = strtok (cstr, " \t\n");
        
		a += pch;

		while(pch != NULL) {
//			printf( " %s\n", pch);

			pch = strtok(NULL, " \t\n");
			if (pch != NULL) a += pch;
		}
	 	const char *C = a.c_str();
	
		v.push_back(cstr);

		if (strcmp(C, "pwd") == 0) getPwd();
		if (strcmp(C, "history") == 0) getHistory(v);

	}

	delete pch;
	delete[] cstr;
	return(0);
}
/*
// Part 2

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
*/

