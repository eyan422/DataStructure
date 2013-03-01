#include <stdio.h>
#include <stdlib.h>
#include <Common.h>

typedef int ElemType;
typedef ElemType *List;

#define INIT_SIZE 100

Status InitList(List *L);
Status DestroyList(List *L);

int main()
{
	List Pointer;
	InitList(&Pointer);
	DestroyList(&Pointer);
	return OK;
}

Status InitList(List *L)
{
	*L = (List)malloc( INIT_SIZE * sizeof(ElemType) );
	if(!(*L))
	{
		printf("Allocation fails\n");
		exit(ERROR);
	}
	else
	{
		printf("Allocation succeed\n");
	}
	
	return OK;
	
}

Status DestroyList(List *L)
{
	if( (*L) != NULL)
	{
		free(*L);
	}
	else
	{
		printf("Free fails\n");
		return ERROR;
	}
	printf("Free succeed\n");
	return OK;
}

