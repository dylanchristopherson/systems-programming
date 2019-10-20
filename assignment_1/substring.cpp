#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	string bigStr, smallStr;

	cout << "String one: ";
	getline(cin, bigStr);
	cout << "String two: ";
	getline(cin, smallStr);

	if (bigStr.find(smallStr) != std::string::npos) {
		std::cout << "FOUND \n";
	}
	else {
		std::cout << "NOT FOUND \n";
	}

	return 0;
}
