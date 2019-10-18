#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;

int main()
{
	size_t Maxsize=80;

 	int fd[2],nbytes;
  
 	char sharedStr1[]="Your full name";
	char sharedStr2[]="your department";
	char sharedStr3[]="add your email address";
 	char readbuffer[80];
	pid_t pid;

 	if(pipe(fd)<0) exit(1);

 	pid = fork();

	if(pid > 0)
	{
		cout << "~in parent process~\n";
		cout << "Writing...\n";
		write(fd[1], sharedStr1, Maxsize);
		write(fd[1], sharedStr2, Maxsize);
		write(fd[1], sharedStr3, Maxsize);

		close(fd[1]);
		wait(0);

	}
	else if (pid < 0)
	{
		cout << "No new child was created \n";
		return 0;
	}
	else
	{

		cout << "~in the child process~\n";

		nbytes=read(fd[0], readbuffer,sizeof(readbuffer));
		cout << readbuffer << endl;
		nbytes=read(fd[0], readbuffer,sizeof(readbuffer));
		cout << readbuffer << endl;
		nbytes=read(fd[0], readbuffer, sizeof(readbuffer));
		cout << readbuffer << endl;

		close(fd[0]);

		exit(0);


		return 0;
	}

return 0;
}
