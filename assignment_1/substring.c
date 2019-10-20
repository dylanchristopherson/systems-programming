#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
	char bigStr[100];
	char smallStr[100];

	printf("Enter a value: \n");
	fgets(bigStr, sizeof(bigStr), stdin);

	printf("Enter another value: \n");
	fgets(smallStr, sizeof(smallStr), stdin);


	if (strstr(bigStr, smallStr) != NULL) {
		printf("FOUND \n");
	}
	else {
		printf("NOT FOUND \n");
	}

	return 0;
}
