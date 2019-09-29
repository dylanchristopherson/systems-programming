#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;


int main()
{

 pid_t pid;
 pid = fork();

 if(pid == 0)
 {
  cout << "A New Child was created \n";
 }
 else if (pid < 0)
 {
  cout << "No new child was created \n";
  return 0;
 }
 else
 {
  cout << "I am the parent :) \n";
  return 0;
 }

return 0;
}
