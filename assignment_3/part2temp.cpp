#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <fcntl.h>

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

//int part4(char * c[], string in) {
	
	
//} 

//int myPipe(char * c[], string in) {
	// Part 5


	
//}
	




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
		
		str = "";

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
		else if (strcmp(cstr, "exit") == 0) exit(1);
		else {

			pid_t  pid;
			int length = tokV.size();

			char * commandString[length+1];

			for (int i = 0; i < length; i++) {
				commandString[i] = (char *) tokV[i].c_str();
			}

			commandString[length] = NULL;


	//		if (length > 2) {
	//			part4(commandString, input);
	//			myPipe(commandString, input);
	//		}
			
//********************************part4**************************************************************

			if (length > 2) {
				if(strcmp(commandString[1], "<") == 0) {
					char *readbuffer[80];	


					cout << "pls" << endl;
					int fda = open(commandString[2], O_RDONLY);
					dup2(fda, 0);	

					char * commander[3];
					commander[0] = commandString[0];
					commander[1] = commandString[2];
					commander[2] = commandString[3];
					pid = fork();
					if(pid == 0) {
						if (execvp(commander[0], commander) < 0) {
							cout<< input << " :command not found\n";
							exit(1);
						}
						dup2(1, fda);
						cout << "HELPPPPP" << endl;
						close(fda);
						
					}
					else if(pid < 0) {
						return 1;
					}
					else{
						wait(0);
						

						
					}
					
					
				}

				if (strcmp(commandString[1], ">") == 0) {
					int fda = creat(commandString[2], O_WRONLY | O_APPEND);

					if (fda < 0) {
						cout << "Can not open the file" << endl;
						exit(1);
					}
					dup2(fda, 1);

					if (execvp(commandString[0], commandString) < 0) {
						cout<< input << " :command not found\n";
						exit(1);
					}

					dup2(fda, 0);
					close(fda);
					
				}

	//********************************part5**********************************************************

				//int fds[2];
				//pid_t  pid;
				
				if(strcmp(commandString[1], "|") == 0) {

					if(pipe(fds)<0) exit(1);
					pid = fork();
					if(pid == 0) 
					{
				
						dup2(fds[1],1);
						close(fds[0]);
					}
					if (execvp(commandString[0], commandString) < 0)
					{
						cout << input << "  :command not found\n";
						exit(0);
					}

					exit(0);

				}
				else if (pid < 0)
				{
					return 0;
				}
				else
				{
					wait(0);
					close(fds[1]);

					dup2(fds[0],0);

					execvp(commandString[2], commandString);

					
				}
			}


			if (length <= 2) {
				pid = fork();
	     			if (pid == 0) {

				    if (execvp(commandString[0], commandString) < 0) {
					cout<< input << " :command not found\n";
					exit(1);
				    }

				}
				else if (pid < 0)   {
					return 1;
				}
				else {
					wait(0);
					
				}
				
				
			}
			//cout << "test3" << endl;
			tokV.erase(tokV.begin(), tokV.end());

		}
		
	}

	delete pch;
	delete[] cstr;
	return(0);

}
