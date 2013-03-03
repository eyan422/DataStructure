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

#define INIT_SIZE 3

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
Status ListTraverse(Node L,void (*visit)());
void print(ElemType e,int i);
Status ListInsert(Node *L,int i,ElemType e);
Status ListDelete(Node *L,int i,ElemType *e);
void listUnion(Node *la,Node lb);

int main()
{
	int result = 0;
	//int (*funcPointer)(ElemType,ElemType) = equal;
	
	Node p;
	Node b;
	//List Pointer;
	InitList(&p);
	InitList(&b);

	PutElem(&p,0,4);
	PutElem(&p,1,5);
	PutElem(&p,2,6);
	GetElem(p,2,&result);
	printf("Get-result<%d>\n",result);

	PutElem(&b,0,1);
	PutElem(&b,1,2);
	PutElem(&b,2,3);
	GetElem(p,2,&result);
	printf("Get-result<%d>\n",result);
	
	ListTraverse(p,print);
	ListTraverse(b,print);
	
	printf("====================\n");
	listUnion(&p,b);
	ListTraverse(p,print);
	printf("====================\n");

	DestroyList(&p);
	DestroyList(&b);
	return OK;
}

void listUnion(Node *la,Node lb)
{
	int la_len = ListLength(*la);
	int lb_len = ListLength(lb);
	int count = 0;
	int result = 0;

	for(count = 0; count < lb_len; count++)
	{
		GetElem(lb,count,&result);
		if( LocateElem(*la,result,equal) == -1)
		{
			ListInsert(la,la_len,result);
			la_len++;
			//ListTraverse(*la,print);
		}
	}
	
}

Status ListInsert(Node *L,int i,ElemType e)
{
	int count = 0;
	
	if( i < 0 || i > ListLength(*L) )
	{
		printf( "i<%d> is out of range[0-%d]\n",i,ListLength(*L) );
		return ERROR;
	}

	List temp = NULL;
	
	temp = (List)realloc((*L).Pointer,((*L).length+1) * sizeof(ElemType) );
	if(temp != NULL)
	{
		(*L).Pointer = temp;
	
		if(i == (*L).length)
		{
			(*L).Pointer[i] = e;
		}
		else if( i == 0)
		{
			for(count = (*L).length - 1; count >= 0; count--)
			{
				(*L).Pointer[count+1] = (*L).Pointer[count];
			}
			(*L).Pointer[i] = e;
		}
		else
		{
			
			for(count = (*L).length - 1;count >= i-1;count--)
			{
				(*L).Pointer[count+1] = (*L).Pointer[count];
			}
			(*L).Pointer[i - 1] = e;
		}
		(*L).length += 1;
	}
	else
	{
		printf("Realloc fails\n");
	}
}

Status ListDelete(Node *L,int i,ElemType *e)
{
	int count = 0;
	
	if( i < 0 || i > ListLength(*L) )
	{
		printf( "i<%d> is out of range[0-%d]\n",i,ListLength(*L) - 1 );
		return ERROR;
	}
	
	*e = (*L).Pointer[i];

	if( i == (*L).length - 1 )
	{
		(*L).length -= 1;
	}
	else if( i == 0 )
	{
		for(count = 1; count <= (*L).length - 1; count++)
		{
			(*L).Pointer[count - 1] = (*L).Pointer[count];	
		}
	}
	else
	{
		for(count = i + 1; count <= (*L).length - 1; count++)
		{
			(*L).Pointer[count - 1] = (*L).Pointer[count];
		}
	}
}

Status ListTraverse(Node L,void (*visit)())
{
	int i = 0;
	int result = 0;
	printf("------------------\n");
	for(i = 0; i < L.length; i++)
	{
		visit(L.Pointer[i],i);
		//result = visit(L.Pointer[i],i);
		/*
		if(result == FALSE)
		{
			return FALSE;
		}
		*/
	}
	printf("------------------\n");
}

void print(ElemType e,int i)
{
	printf("e%d<%d>\n",i,e);
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
		printf("i is out of range[0-%d]\n",ListLength(*L));
		return ERROR;
	}	
	
	((*L).Pointer)[i] = e;
}

Status GetElem(Node L,int i,ElemType *e)
{
	if( i < 0 || i > ListLength(L) )
	{
		printf("i is out of range[0-%d]\n",ListLength(L));
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
			printf("The element locates at %d\n",i);
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
	return -1;
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
	(*L).Pointer = (List)malloc(INIT_SIZE * sizeof(ElemType));
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
	memset((*L).Pointer,0,sizeof((*L).Pointer));
	return OK;
	
}

Status DestroyList(Node *L)
{
	if( (*L).Pointer != NULL)
	{
		printf("free list\n");
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

