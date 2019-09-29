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
 char sharedStr[]="Hello, CS442!\n";
 char readbuffer[80];
 pid_t pid;

 if(pipe(fd)<0) exit(1);

 pid = fork();

 if(pid == 0)
 {
  cout << "A New Child was created \n";

  for(int i = 0; i < 2; i++) {
	cout << "TEST: " << i << endl;
  }

 close(fd[0]);

 write(fd[1], sharedStr, Maxsize);
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
       	close(fd[1]);

	nbytes=read(fd[0], readbuffer,sizeof(readbuffer));
	
	cout << "Readbuffer: " << readbuffer << endl;	
	
	
	cout << "I am the parent :) \n";


  return 0;
 }

return 0;
}
