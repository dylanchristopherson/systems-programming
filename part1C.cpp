#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

int main()
{
	size_t Maxsize=80;
 	int fds[2],nbytes; 
 	char sharedStr1[]="Your full name";
	char sharedStr2[]="your department";
	char sharedStr3[]="add your email address";
 	char readbuffer[80];
	pid_t pid;

 	if(pipe(fds)<0) exit(1);

 	pid = fork();
	


	if(pid == 0)
 	{
		cout << "A New Child was created \n";
		dup2(fds[1],1);
		close(fds[0]);
		
		cout << "test1" << endl;
		cout << "test2" << endl;
		cout << "test3" << endl;

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

		cin >> readbuffer;
		cout << "Readbuffer: " << readbuffer << endl;

		cin >> readbuffer;
		cout << "Readbuffer: " << readbuffer << endl;

		cin >> readbuffer;
		cout << "Readbuffer: " << readbuffer << endl;

		return 0;
	}

return 0;
}
