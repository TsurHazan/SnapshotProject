#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#pragma warning(disable:4996)


int main() {

	int a = 150;
	int b = 75;
	char c = 0;

	while (c != 'E')
	{
		printf("\nPress '+' to add\nPress '-' to minus\nPress 'X' to multiply\nPress '/' to divide\nPress 'E' to exit: ");
		c = getch();

		switch (c)
		{
		case '+': printf("\n\n %d + %d = %d \n",a,b,a+b);
			break;

		case '-': printf("\n\n %d - %d = %d \n",a,b,a-b);
			break;

		case 'X': printf("\n\n %d * %d = %d \n",a,b,a*b);
			break;

		case '/':printf("\n\n %d / %d = %d \n",a,b,a/b);
			break;

		case 'E':c='E';
			break;

		default:
			printf("\nPlease enter a valid char\n");
			break;
		}
		

	}

	return 0;
}