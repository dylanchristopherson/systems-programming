#include<iostream>
#include<cstring>
#include<stdio.h>
#include<string.h>

using namespace std;

int main() {

	string str;
	cout << "Please enter a string \n";
	getline(cin, str);;

	char * cstr = new char [str.length()+1];
	strcpy(cstr, str.c_str());

	string a;

	char * pch;
        pch = strtok (cstr, " \t\n");
        
	a += pch;

	while(pch != NULL) {
		printf( " %s\n", pch);

		pch = strtok(NULL, " \t\n");
		if (pch != NULL) a += pch;
	}
	const char *C = a.c_str();
	cout << "Final c_str: " << C << endl;

	
	delete[] cstr;
	delete pch;
	return(0);
}


