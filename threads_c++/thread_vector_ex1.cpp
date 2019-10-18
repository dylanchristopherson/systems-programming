#include <iostream>
#include <thread>

using namespace std;

void greeting(void) {
	cout << "Hello, CS442 students!\n";
	cout << "This is a thread " << this_thread::get_id() << endl;
}

int main(void) {
	thread myThread(greeting);

	myThread.join(); // Needed so program doesn't end before thread

	cout << "by main thread " << this_thread::get_id() << endl;
 
	return 0;
}	
