#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <string>

#include <unistd.h>
#include <iostream>

#include <sys/wait.h>
#include <sys/types.h>

#include <fcntl.h>

using namespace std;

int main()
{

	// part 5 read from file 
	int fd = open("dup2test.txt", O_WRONLY | O_APPEND);
	
	if (fd < 0) 
	{
		cout << "Can not open the file" << endl;
		exit(1);
	}
	 
	
	dup2(fd, 1);
	cout << "I will be written to the file dup2test.txt" << endl;

	string msg1 = "I am Dylan Christopherson";
	string msg2 = "Test";
	cout << msg1;
		
	close(fd);

	return(0);
}
