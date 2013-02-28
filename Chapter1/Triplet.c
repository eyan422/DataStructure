#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Common.h>

typedef int ElemType;

typedef ElemType *Triplet;

Status InitTriplet(Triplet *T,ElemType v1,ElemType v2,ElemType v3);
Status DestroyTriplet(Triplet *T);

int main()
{
	Triplet Pointer = NULL;
	InitTriplet(&Pointer,1,2,3);
	printf("%d\n",*Pointer);
	DestroyTriplet(&Pointer);
	return 0;
}

Status InitTriplet(Triplet *T,ElemType v1,ElemType v2,ElemType v3)
{
	*T = (ElemType *)malloc( 3 * sizeof(ElemType));
	
	if( !(*T) )
	{
		printf("OVERFLOW");
		exit(OVERFLOW);
	}
	
	(*T)[0] = v1;
	//T[1] = v2;
	//T[2] = v3;

	printf("Alllcation is successful\n");
	
	return OK;
}

Status DestroyTriplet(Triplet *T)
{
	free(*T);
	*T = NULL;

	return OK;
}
