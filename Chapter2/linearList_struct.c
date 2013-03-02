#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Common.h>

typedef int ElemType;
typedef ElemType *List;

typedef struct
{
	List Pointer;
	int length;
}Node;

#define INIT_SIZE 10

Status InitList(Node *L);
Status DestroyList(Node *L);
Status ClearList(List *L);
Status ListEmpty(List L);
Status ListLength(Node L);
Status GetElem(Node L,int i,ElemType *e);
Status PutElem(Node *L,int i,ElemType e);
Status LocateElem(Node L,ElemType e,int (*compare)());
Status equal(ElemType p1,ElemType e2);
Status PriorElem(Node L,ElemType cur,ElemType *pre);
Status NextElem(Node L,ElemType cur,ElemType *next);
Status ListTraverse(List L,int (*visit)());
int print(ElemType e);
void ListInsert(List *L,int i,ElemType e);
void ListDelete(List *L,int i,ElemType e);

int main()
{
	int result = 0;
	//int (*funcPointer)(ElemType,ElemType) = equal;
	
	Node p;
	//List Pointer;
	InitList(&p);

	/*
	ClearList(&Pointer);
	*/
	result = ListEmpty(p.Pointer);
	printf("result<%s>\n",result==TRUE?"Empty":"!Empty");	

	result = ListLength(p);
	printf("Length<%d>\n",result);
	
	PutElem(&(p),2,5);
	PutElem(&(p),1,4);
	PutElem(&(p),3,6);
	GetElem(p,2,&result);
	printf("Get-result<%d>\n",result);

	//LocateElem(Pointer,5,funcPointer);
	LocateElem(p,5,equal);
	
	PriorElem(p,5,&result);
	printf("Prior-result<%d>\n",result);

	NextElem(p,5,&result);
	printf("Next-result<%d>\n",result);
	
	//funcPointer = print;
	
	ListTraverse(p.Pointer,print);
	//ListTraverse(Pointer,funcPointer);
	
	DestroyList(&p);
	return OK;
}

Status ListTraverse(List L,int (*visit)())
{
	int i = 0;
	int result = 0;
	for(i = 0; i < INIT_SIZE; i++)
	{
		result = visit(L[i]);
		if(result == FALSE)
		{
			return FALSE;
		}
	}
}

int print(ElemType e)
{
	printf("e<%d>\n",e);
}

Status PriorElem(Node L,ElemType cur,ElemType *pre)
{
	int result = 0;
	result =  LocateElem(L,cur,equal);

	if( result != FALSE && result != 0)
	{
		*pre = (L.Pointer)[result - 1];
	}
}

Status NextElem(Node L,ElemType cur,ElemType *next)
{
	int result = 0;
	result =  LocateElem(L,cur,equal);

	if( result != FALSE && result != INIT_SIZE - 1)
	{
		*next = (L.Pointer)[result + 1];
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
Status PutElem(Node *L,int i,ElemType e)
{
	if( i < 0 || i > ListLength(*L) )
	{
		printf("i is out of range[0-%d]",ListLength(*L));
		return ERROR;
	}	
	
	((*L).Pointer)[i] = e;
}

Status GetElem(Node L,int i,ElemType *e)
{
	if( i < 0 || i > ListLength(L) )
	{
		printf("i is out of range[0-%d]",ListLength(L));
		return ERROR;
	}	
	
	*e = (L.Pointer)[i];
}

Status LocateElem(Node L,ElemType e,int (*compare)())
{
	int i = 0;
	for(i = 0; i < ListLength(L); i++)
	{
		if( compare((L.Pointer)[i],e) == TRUE )
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

Status ListLength(Node L)
{
	if(L.Pointer != NULL)
	{
		return L.length;
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

Status InitList(Node *L)
{
	int i = 0;
	(*L).Pointer = (List)malloc( INIT_SIZE * sizeof(ElemType) );
	if( !((*L).Pointer) )
	{
		printf("Allocation fails\n");
		exit(ERROR);
	}
	else
	{
		printf("Allocation succeed\n");
		(*L).length = INIT_SIZE;
	}
	
	/*
	for(i = 0; i < INIT_SIZE; i++)
	{
		(*L)[i] = 0;
	}
	*/
	memset((*L).Pointer,0,sizeof( (*L).Pointer) );
	return OK;
	
}

Status DestroyList(Node *L)
{
	if( (*L).Pointer != NULL)
	{
		free((*L).Pointer);
	}
	else
	{
		printf("Free fails\n");
		return ERROR;
	}
	printf("Free succeed\n");
	return OK;
}

