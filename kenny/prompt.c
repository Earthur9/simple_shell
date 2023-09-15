#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t n = 0;
	char *buf = NULL;

	//buf = malloc(sizeof(char) * 10);
	printf("$ ");
	getline(&buf, &n, stdin);
	printf("%s",buf);
	//printf("Buffer Size : %ld\n", n);

	free(buf);
	return (0);
}
