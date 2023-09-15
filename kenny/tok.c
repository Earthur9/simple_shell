#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char str[] = "This is a separated word by spaces";
	char delim[] = " ";
	char *copy;
	char *trunks;

	copy = strcpy(malloc(strlen(str) + 1), str);
	
	if (copy != NULL)
	{
		trunks = strtok(copy, delim);
		
		while (trunks != NULL)
		{
			printf("%s\n", trunks);
			trunks = strtok(NULL, delim);
		}
	}
	return (0);
}
