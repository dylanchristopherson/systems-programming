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

	size_t maxsize=80;
 	int fds[2],nbytes; 
 	char readbuffer[80];

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


			if(strcmp(commandString[1], "|") == 0) {
				cout << "Pipe found" << endl;
				pid_t pid;

 				if(pipe(fds)<0) exit(1);
			
 				pid = fork();
	


				if(pid == 0)
 				{
					//cout << "A New Child was created \n";
					dup2(fds[1],1);
					close(fds[0]);
		
					if (execvp(commandString[0], commandString) < 0) {
						cout << input << "  :command not found\n";
						exit(0);
					}

					exit(0);
	
				}
				else if (pid < 0)
				{
					cout << "No new child was created \n";
					return 0;
				}
				else
				{
					wait(0);
       					close(fds[1]);
		
					dup2(fds[0],0);

					execvp(commandString[2], commandString);

					return 0;
				}
			}
			pid = fork();
     			if (pid == 0) {

		            if (execvp(commandString[0], commandString) < 0) {
				cout<< input << " :command not found\n";
				exit(1);
		            }

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
