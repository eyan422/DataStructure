#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Common.h>

typedef int ElemType;
typedef ElemType *List;

#define INIT_SIZE 10

Status InitList(List *L);
Status DestroyList(List *L);
Status ClearList(List *L);
Status ListEmpty(List L);
Status ListLength(List L);
Status GetElem(List L,int i,ElemType *e);
Status PutElem(List *L,int i,ElemType e);
Status LocateElem(List L,ElemType e,int (*compare)());
Status equal(ElemType p1,ElemType e2);
Status PriorElem(List L,ElemType cur,ElemType *pre);
Status NextElem(List L,ElemType cur,ElemType *next);

int main()
{
	int result = 0;
	int (*funcPointer)(ElemType,ElemType) = equal;

	List Pointer;
	InitList(&Pointer);

	/*
	ClearList(&Pointer);
	*/
	result = ListEmpty(Pointer);
	printf("result<%s>\n",result==TRUE?"Empty":"!Empty");	

	result = ListLength(Pointer);
	printf("Length<%d>\n",result);
	
	PutElem(&Pointer,2,5);
	PutElem(&Pointer,1,4);
	PutElem(&Pointer,3,6);
	GetElem(Pointer,2,&result);
	printf("Get-result<%d>\n",result);

	LocateElem(Pointer,5,funcPointer);
	
	PriorElem(Pointer,5,&result);
	printf("Prior-result<%d>\n",result);

	NextElem(Pointer,5,&result);
	printf("Next-result<%d>\n",result);

	DestroyList(&Pointer);
	return OK;
}

Status PriorElem(List L,ElemType cur,ElemType *pre)
{
	int result = 0;
	result =  LocateElem(L,cur,equal);

	if( result != FALSE && result != 0)
	{
		*pre = L[result - 1];
	}
}

Status NextElem(List L,ElemType cur,ElemType *next)
{
	int result = 0;
	result =  LocateElem(L,cur,equal);

	if( result != FALSE && result != INIT_SIZE - 1)
	{
		*next = L[result + 1];
	}
}

Status equal(ElemType p1,ElemType p2)
{
	//printf("p1<%d>,p2<%d>\n",p1,p2);
	if(p1 == p2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
Status PutElem(List *L,int i,ElemType e)
{
	if( i < 0 || i > ListLength(*L) )
	{
		printf("i is out of range[0-%d]",ListLength(*L));
		return ERROR;
	}	
	
	(*L)[i] = e;
}

Status GetElem(List L,int i,ElemType *e)
{
	if( i < 0 || i > ListLength(L) )
	{
		printf("i is out of range[0-%d]",ListLength(L));
		return ERROR;
	}	
	
	*e = L[i];
}

Status LocateElem(List L,ElemType e,int (*compare)())
{
	int i = 0;
	for(i = 0; i < ListLength(L); i++)
	{
		if( compare(L[i],e) == TRUE )
		{
			//printf("The element locates at %d\n",i);
			return i;
		}
		/*
		else
		{
			printf("Element does not exist\n");
			return FALSE;
		}
		*/
	}
	return FALSE;
}

Status ListLength(List L)
{
	if(L != NULL)
	{
		return INIT_SIZE;
	}
}

Status ListEmpty(List L)
{
	if( !L )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Status ClearList(List *L)
{
	int i = 0;
	/*
	if(!(*L))
	{
		for(i=0; i< sizeof(*L)-1;i++)
		{
			(*L)[i] = -1;
		}
	}
	*/
	if( !(*L) )
	{
		*L = NULL;
		return OK;
	}
}

Status InitList(List *L)
{
	int i = 0;
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
	
	/*
	for(i = 0; i < INIT_SIZE; i++)
	{
		(*L)[i] = 0;
	}
	*/
	memset(*L,0,sizeof(*L));
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

