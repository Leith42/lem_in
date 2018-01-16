#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Hello, World!\n");

	char *str = malloc(50);
	free(str);
	return 0;
}