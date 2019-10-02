#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>


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
		
		v.push_back(cstr);

		if (strcmp(cstr, "pwd") == 0) getPwd();
		else if (strcmp(cstr, "history") == 0) getHistory(v);
		else {
			cout << "Test" << endl;	
	
			pid_t  pid;  
			char * commandString[2];

//			commandString[0]=a.c_str();
			// Need to use strcpy because c_str returns
			// a const char, and commandString isn't a
			// const char
			strcpy(commandString[0], a.c_str());
			commandString[1]=NULL;       				

			pid = fork(); 
     			if (pid == 0) {

		            if (execvp(commandString[0], commandString) < 0) {
				cout<<"*** ERROR: exec failed\n";     
				exit(1);
		            }
			    cout<<"A New Child was created J \n";
			 } else if (pid < 0)   { 
				cout<<"No New Child Was created L\n"; 
				return 1;
			}
			else // must be the parent
                        {  
			wait(0);
		 	cout<<"I am the parent :)\n";   
			}	 
		}
	}
	delete pch;
	delete[] cstr;
	return(0);
}


