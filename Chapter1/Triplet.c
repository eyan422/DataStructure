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
Status IsAscending(Triplet T);
Status IsDescending(Triplet T);
Status Max(Triplet T, ElemType *e);
Status Min(Triplet T, ElemType *e);

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
	
	IsAscending(Pointer);
	IsDescending(Pointer);
	
	Max(Pointer,&e);
	printf("e-max:%d\n",e);
	Min(Pointer,&e);
	printf("e-min:%d\n",e);

	DestroyTriplet(&Pointer);
	return 0;
}

Status IsAscending(Triplet T)
{
	if( T[0] <= T[1] && T[1] <= T[2]  )
	{
		printf("Triplet is ascending\n");
	}
	else
	{
		printf("Triplet is not ascending\n");
	}
	
	return OK;
}

Status IsDescending(Triplet T)
{
	if( T[0] >= T[1] && T[1] >= T[2]  )
	{
		printf("Triplet is Descending\n");
	}
	else
	{
		printf("Triplet is not descending\n");
	}
	
	return OK;
}

Status Max(Triplet T, ElemType *e)
{
	int i = 0;
	*e = T[0];
	for(i = 1; i < 3; i++)
	{
		if(T[i] > *e)
		{
			*e = T[i];
		}
	}
}

Status Min(Triplet T, ElemType *e)
{
	int i = 0;
	*e = T[0];
	for(i = 1; i < 3; i++)
	{
		if(T[i] < *e)
		{
			*e = T[i];
		}
	}
}

Status Put(Triplet *T,int i,ElemType e)
{
	if( i < 0 || i >3 )
	{
		printf("i is out of range[0-2]\n");
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
		printf("i is out of range[0-2]\n");
		exit(ERROR);
	}

	*e = T[i];
	
	return OK;
}
