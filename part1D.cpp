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

	cout << Readbuffer;
}

void getHistory(vector<string> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << i+1 << " " << v[i] << endl; 
	}
}

int main() {

	string str;
	string a;
	vector<string> v;
//	vector<string> tokV;

	char * cstr;
	char * pch;
	char *C;

	while(1) {
		getPwd();
		cout<<"~> ";

		vector<string> tokV;

		getline(cin,str);
		v.push_back(str);

		cstr = new char [str.length()+1];
		
		cstr=(char *) str.c_str();

	        pch = strtok (cstr, " \t\n");
        
		a += pch;
		tokV.push_back(pch);

		while(pch != NULL) {
	
			pch = strtok(NULL, " \t\n");
			if (pch != NULL) {
				a += pch;
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
				cout << "Char test: " << (char *) tokV[i].c_str() << endl;
			}	

			commandString[length+1] = NULL;

			for (int i = 0; i < length+1; i++) {
				cout << "comstr: " << commandString[i] << endl;
			}			
/*
//1: tokenize your command (command and arguments)
//make the following array as large as number of the tokens +1
char * commandString[2];  //replace 2 with n+1 : n is number of the tokens
//iterate over the tokens array and copy the tokens into thr commandString array

string command="ls";
commandString[0]=(char *) command.c_str(); //replace the command with the vector array elements

			//strcpy(commandString[0],  "ls"); //loop

			commandString[1]=NULL;  // replace 1 with n such that n //is the number of the tokens so the Null will be in the last array element     				
*/

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

			tokV.erase(tokV.begin(), tokV.end());	 
		}
	}
	delete pch;
	delete[] cstr;
	return(0);
}


