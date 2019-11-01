#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

// Test

int execvp_func(char * c[], string input);
void getPwd2();
void getPwd();
void getHistory(vector<string> v);
int part4(char * c[], string in, int index, int length);
int myPipe(char * c[], string in, int index, int length);

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

	bool flag = true;


	while(1) {
		
		str = "";

	
		getPwd2();
		cout<<"$ ";

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

		

			for (int i = 0; i < length; i++) {

				if (strcmp(commandString[i], ">") == 0) {
					cout << "Test if this works: " << i << endl;
					flag = false;
					pid = fork();
					if(pid == 0) {
						part4(commandString, input, i, length);
					}
					else if (pid < 0) {
						return 1;
					}
					else {
						wait(0);
					}
				}

				else if (strcmp(commandString[i], "<") == 0) {
					cout << "Test if this works: " << i << endl;
					flag = false;
					pid = fork();
					if(pid == 0) {
						part4(commandString, input, i, length);
					}
					else if (pid < 0) {
						return 1;
					}
					else {
						wait(0);
					}
				}

				else if (strcmp(commandString[i], "|") == 0) {
					cout << "Test if this works: " << i << endl;
					flag = false;
					cout << "Length: " << length;
					pid = fork();
					if(pid == 0) {
						myPipe(commandString, input, i, length);
					}
					else if (pid < 0) {
						return 1;
					}
					else {
						wait(0);
					}
				}

			}


			if (flag == true) {
				execvp_func(commandString, input);
			}

			// Clears tokenized vector
			tokV.erase(tokV.begin(), tokV.end());
			flag = true;

		}
		
	}
	delete pch;
	delete[] cstr;
	return(0);
}

/****************************************/
// Functions
/****************************************/


int execvp_func(char * c[], string input) {
	pid_t pid;
	pid = fork();
	if (pid == 0) {

	    if (execvp(c[0], c) < 0) {
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
	

	return(0);
}

void getPwd2() {

	size_t Maxsize = 80;
	char Readbuffer[80];

	getcwd(Readbuffer, Maxsize);

	printf("\x1B[31m~%s\033[0m",Readbuffer);
}

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

// part4 is called in a fork in main, that's why we don't need to fork when
// using execvp
int part4(char * commandString[], string in, int index, int length) {
	
	char * c1[index+1];
	char * c2[length - index - 1];
	
	for (int i = 0; i <= index; i ++) {
		c1[i] = commandString[i];
	}
	c1[index] = NULL;

	for (int i = 0; i < length - index -1; i ++) {
		c2[i] = commandString[i+ index + 1];
	}

	if(strcmp(commandString[index], "<") == 0) {
		char *readbuffer[80];	

		int fda = open(c2[0], O_RDONLY);
		dup2(fda, 0);	

		if (execvp(c1[0], c1) < 0) {
			cout<< in << " :command not found\n";
			exit(1);
		}
	
		dup2(fda,1);
		
		close(fda);
		return(0);
		
	}

	if (strcmp(commandString[index], ">") == 0) {
		int fda = open(c2[0], O_WRONLY | O_CREAT | S_IRWXU, 00700);

		if (fda < 0) {
			cout << "Can not open the file" << endl;
			exit(1);
		}
		dup2(fda, 1);

		if (execvp(c1[0], c1) < 0) {
			cout<< in << " :command not found\n";
			exit(1);
                }

		dup2(fda, 0);
		close(fda);
		return(0);
	}
	return(0);
} 

// myPipe is called in a fork in main, that's why we don't need to fork when
// using execvp
int myPipe(char * commandString[], string in, int index, int length) {
	// Part 5


	char * c1[index+1];
	char * c2[length - index];
	
	for (int i = 0; i <= index; i ++) {
		c1[i] = commandString[i];
	}
	c1[index] = NULL;

	for (int i = 0; i < length - index; i ++) {
		c2[i] = commandString[i+ index + 1];
	}

	int fds[2];
	pid_t  pid;
	
	if(strcmp(commandString[index], "|") == 0) {

		if(pipe(fds)<0) exit(1);

		pid = fork();
		if(pid == 0) 
		{
	
			dup2(fds[1],1);
			close(fds[0]);

			if (execvp(c1[0], c1) < 0)
			{
				cout << in << "  :command not found\n";
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

			execvp(c2[0], c2);

			return 0;
		}
	}
}
