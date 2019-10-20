#include<string.h>
#include<iostream>


int main() {
	int num;

	srand (time(NULL));

	for(int i = 0; i < 10; i++) {
		num = rand() % 1001;
		std::cout << num << std::endl;
	}
}
