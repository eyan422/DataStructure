#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char pclString[] = "Hello";

	printf("strlen<%d>,sizeof(%d)\n",(int)strlen(pclString),(int)sizeof(pclString));

	return 0;
}

