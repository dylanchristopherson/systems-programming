#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/wait.h>

using namespace std;

int main() {
	pid_t pid;
	pid=fork();

	if(pid==0) // Means you are inside child process
		cout << "A new child was created\n";
	else if(pid < 0)
		cout << "Something bad happened";
	else {
		wait(0);
		cout << "I am the parent\n";
	}

	return(0);
}
