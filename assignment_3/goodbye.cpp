#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int main() {

	string goodbye;
	string compare;
	cin >> goodbye;
	

	char * cstr = new char [goodbye.length()+1];
	cstr=(char *) goodbye.c_str();

	if (strcmp(cstr, "hello") == 0)
	{
		cout << "No, goodbye world" << endl;
	} 
	else {
		cout << "Failed" << endl;
	}

}
