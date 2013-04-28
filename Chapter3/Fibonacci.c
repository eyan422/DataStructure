#include <stdio.h>
#include <stdlib.h>

int Fibo(int n);

int main()
{	
	int result = 0;
	result = Fibo(5);

	printf("result<%d>\n",result);

	return 0;
}


int Fibo(int n)
{
	if(n == 0)
	{
		return 0;
	}
	if(n == 1)
	{
		return 1;
	}
	else
	{
		return Fibo(n-1) + Fibo(n-2);
	}
}

