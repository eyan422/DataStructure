#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Common.h>

typedef int ElemType;

typedef ElemType *Triplet;

Status InitTriplet(Triplet *T,ElemType v1,ElemType v2,ElemType v3);
Status DestroyTriplet(Triplet *T);
Status Get(Triplet T,int i,ElemType *e);
Status Put(Triplet *T,int i,ElemType e);

int main()
{
	Triplet Pointer = NULL;
	ElemType e = 0;
	InitTriplet(&Pointer,1,2,3);
	
	Get(Pointer,1,&e);
	printf("e1:%d\n",e);
	
	Put(&Pointer,1,5);
	Get(Pointer,1,&e);
	
	printf("e1:%d\n",e);
	
	DestroyTriplet(&Pointer);
	return 0;
}

Status Put(Triplet *T,int i,ElemType e)
{
	if( i < 0 || i >3 )
	{
		printf("i is out of range[0-2]");
		exit(ERROR);
	}

	(*T)[i] = e;
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
	(*T)[1] = v2;
	(*T)[2] = v3;

	printf("Allocation is successful\n");
	
	return OK;
}

Status DestroyTriplet(Triplet *T)
{
	free(*T);
	*T = NULL;
	
	printf("Dellocation is successful\n");

	return OK;
}

Status Get(Triplet T,int i,ElemType *e)
{
	if( i < 0 || i > 3)
	{
		printf("i is out of range[0-2]");
		exit(ERROR);
	}

	*e = T[i];
	
	return OK;
}
