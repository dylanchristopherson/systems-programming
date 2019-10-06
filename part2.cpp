#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>

using namespace std;

void getPwd() {

	size_t Maxsize = 80;
	char Readbuffer[80];

	getcwd(Readbuffer, Maxsize);

	cout << Readbuffer;
}

void getHistory(vector<string> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << "   " << i+1 << " " << v[i] << endl;
	}
}

int main() {

	string str;
	string input;
	vector<string> v;

	char * cstr;
	char * pch;
	char *C;

	while(1) {
		getPwd();
		cout<<"~> ";

		vector<string> tokV;

		getline(cin,str);
		input = str;
		v.push_back(str);

		cstr = new char [str.length()+1];

		cstr=(char *) str.c_str();
	        pch = strtok (cstr, " \t\n");

		tokV.push_back(pch);

		while(pch != NULL) {

			pch = strtok(NULL, " \t\n");
			if (pch != NULL) {
				tokV.push_back(pch);
			}
		}

		if (strcmp(cstr, "pwd") == 0){ getPwd(); cout<<endl;}
		else if (strcmp(cstr, "history") == 0) getHistory(v);
		else {

			pid_t  pid;
			int length = tokV.size();

			char * commandString[length+1];

			for (int i = 0; i < length; i++) {
				commandString[i] = (char *) tokV[i].c_str();

			}
			commandString[length] = NULL;

			pid = fork();
     			if (pid == 0) {

		            if (execvp(commandString[0], commandString) < 0) {
				cout<< input << " :command not found\n";
				exit(1);
		            }
			    cout<<"A New Child was created J \n";
			 } else if (pid < 0)   {
				cout<<"No New Child Was created L\n";
				return 1;
			}
			else {
				wait(0);
			}

			tokV.erase(tokV.begin(), tokV.end());
		}
	}
	delete pch;
	delete[] cstr;
	return(0);
}
