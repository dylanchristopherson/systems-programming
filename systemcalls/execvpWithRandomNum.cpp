//By Dr. Alnaeli
//How execvp works to change a process' execution image to make it run something different from the parent process
//Please notice that I am using hard-coding way when it comes to forming the command.
// this program  will make the child process run the following unix command (ls -l)
#include  <stdio.h>
#include <unistd.h>
#include  <iostream>
#include  <sys/wait.h>
#include <unistd.h>
#include  <string>

using namespace std;

int  main()  {     
pid_t  pid;  
char * commandString[2];

string command="./randomNum";   // this is the ls unix command

commandString[0]=(char*) command.c_str();  //this is how to conver a string variable to a c_string
commandString[1]=NULL;

     pid = fork();

     if (pid == 0) { // a child was created and you are inside it J

            if (execvp(commandString[0], commandString) < 0) {    // try to change the execution impage of the child
				//here using the execvp, the impage of execution will be replaced for the child by: ls -l. 
				//If it returns a negative value, that means something went wrong
                cout<<"*** ERROR: exec failed\n";     
				exit(1);
            }
        cout<<"A New Child was created J \n";  // will not execute this line since  //image of execution has been changed by execvp system call
	 } else if (pid < 0)   {   // no new child was created (fail)
			cout<<"No New Child Was created L\n"; 
			return 1;
	}
	else // must be the parent
    {  
		wait(0); // must wait for a child to finish
	    cout<<"I am the parent :)\n";   
	}

return 0;    
}   //end of main method
