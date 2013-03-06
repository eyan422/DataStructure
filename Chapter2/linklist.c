#include <Common.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct lnode
{
	ElemType data;
	struct lnode *next;
}lnode,*linklist;

void traverse(linklist head, void(*func)());
void createHead(linklist *head,int size);
void createTail(linklist *head,int size);
void destroy(linklist *head);
void print(int num);
Status insert(linklist *head,int i,ElemType e);
Status merge(linklist la,linklist lb,linklist *lc);
Status insertTail(linklist *head,ElemType e);
Status Clear(linklist *head);
Status ListEmpty(linklist head);
int ListLength(linklist head,char *string);
Status GetElem(linklist head,int i,ElemType *e);
Status PutElem(linklist *head,int i,ElemType e);
Status LocateElem(linklist head,ElemType e,int (*compare)());
Status equal(ElemType p1, ElemType p2);
Status PrioElem(linklist head, ElemType cur, ElemType *prev);
Status NextElem(linklist head, ElemType cur, ElemType *next);

int main()
{
	ElemType result = 0;
	linklist head;
	createHead(&head,5);
	traverse(head,print);

	//insert(&head,2,9);
	insertTail(&head,10);	
	insertTail(&head,12);	
	traverse(head,print);
	
	linklist tail;
	createTail(&tail,7);
	traverse(tail,print);
	insertTail(&tail,9);	
	insertTail(&tail,11);	
	//insert(&tail,2,12);
	traverse(tail,print);

	linklist test;
	createHead(&test,1);
	traverse(test,print);
	merge(head,tail,&test);
	traverse(test,print);
	
	Clear(&test);
	printf("-----clear-----\n");
	traverse(test,print);
	
	linklist empty = NULL;
	empty = (linklist)malloc(sizeof(lnode));
	empty->next = NULL;
	empty->data = 0;
	ListEmpty(empty);	

	ListLength(head,"head");
	ListLength(tail,"tail");
	ListLength(test,"test");
	
	GetElem(head,2,&result);
	traverse(head,print);
	PutElem(&head,3,result);
	traverse(head,print);
	
	LocateElem(head,result,equal);
	PrioElem(head,result,&result);
	traverse(head,print);

	destroy(&head);
	destroy(&tail);
	destroy(&test);
	return OK;
}

Status PrioElem(linklist head,ElemType e,ElemType *prev)
{
	int count = 0;
	char *pclFunc = "PrioElem";
	linklist cur = head;
	linklist pre = cur;

	if(head == NULL)
	{
		printf("%s head is NULL\n",pclFunc);
		return ERROR;
	}
	else
	{
		while(cur != NULL)
		{
			pre = cur;
			cur = cur->next;
			count++;

			if(cur->data == e)
			{
				*prev = pre->data;
				printf("%s The cur is <%d>[%d],the prev is <%d>[%d]\n",pclFunc,e,count,*prev,count-1);
				return OK;
			}
		}
		return FALSE;
	}
}

Status NextElem(linklist head,ElemType cur,ElemType *next)
{

}

Status equal(ElemType p1, ElemType p2)
{
	if(p1 == p2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

Status GetElem(linklist head,int i,ElemType *e)
{
	int count = 0;
	char *pclFunc = "GetElem";
	
	linklist index = head;
	
	if(head != NULL)
	{	
		if(i < 0 || i > (ListLength(head,pclFunc) - 1) )
		{
			printf( "%s i is out of range[0-%d]\n",pclFunc,(ListLength(head,pclFunc)-1) );
		}
		else
		{
		 	for(count = 0; count < i; count++)
			{
				index = index->next;		
			}
			*e = index->data;
			printf("%s data<%d>\n",pclFunc,*e);
		}
	}
	else
	{
		printf("%s head is NULL\n",pclFunc);
	}
}

Status PutElem(linklist *head,int i,ElemType e)
{
	int count = 0;
	char *pclFunc = "PutElem";
	linklist index = *head;
	
	if(index != NULL)
	{
		if(i < 0 || i > (ListLength(*head,pclFunc) - 1))
		{
			printf( "%s i is out of range[0-%d]\n",pclFunc,(ListLength(*head,pclFunc)-1) );
		}
		else
		{
			for(count = 0; count < i; count++)
			{
				index = index->next;
			}
			index->data = e;
			printf("%s data<%d>\n",pclFunc,index->data);
		}
	}
	else
	{
		printf("\n");
	}
}

Status LocateElem(linklist head,ElemType e,int (*compare)())
{
	int count = 0;
	char *pclFunc = "LocateElem";

	linklist index = head;

	while(index != NULL)
	{
		if(compare(index->data,e) == TRUE)
		{
			printf("%s The element<%d> locates at[%d]\n",pclFunc,e,count);
			return OK;
		}
		
		index = index->next;
		count++;
	}

	return FALSE;
}

int ListLength(linklist head, char *string)
{
	int length = 0;
	linklist index = head;
	if(head != NULL)
	{
		while(index != NULL)
		{
			index = index->next;
			length++;
		}
		printf("[%s]length is <%d>\n",string,length);
	}	
	else
	{
		printf("head is null\n");
	}
}

Status ListEmpty(linklist head)
{
	if(head != NULL)
	{
		if(head->next == NULL)
		{	
			printf("list is empty\n");
			return TRUE;
		}
		else
		{
			printf("list is not empty\n");
			return FALSE;
		}
	}
	else
	{
		printf("head is null\n");
	}
}

Status Clear(linklist *head)
{
	linklist index = *head;
	while(index != NULL)
	{
		index->data = 0;
		index = index->next;
	}
	return OK;
}

Status insertTail(linklist *head,ElemType e)
{
	linklist index = *head;
	linklist tmp = NULL;
	while(index->next != NULL)
	{
		index = index->next;
	}
	
	tmp = (linklist)malloc(sizeof(lnode));
	tmp->data = e;
	tmp->next = NULL;

	index->next = tmp;

	return OK;
}

Status merge(linklist la,linklist lb,linklist *lc)
{
	linklist pa = la;
	linklist pb = lb;
	linklist index = *lc;
	
	while( (pa->next != NULL) && (pb->next != NULL) )
	{
		if( (*pa).data > (*pb).data )
		{
			insertTail(lc,pa->data);
			//pa = pa->next;
		}
		else
		{
			insertTail(lc,pb->data);
			//pb = pb->next;
		}
		pa = pa->next;
		pb = pb->next;
	}
	
	while(pa != NULL)
	{
		insertTail(lc,pa->data);
		pa = pa->next;	
	}
	
	while(pb != NULL)
	{
		while(index->next != NULL)
		{
			index= index->next;
		}
		
		printf("lc final element<%d>\n",index->data);		
		
		if(index->data < pb->data)
		{
			insertTail(lc,pb->data);
		}
		pb = pb->next;
	}
	
}

void createTail(linklist *head,int size)
{
	int i = 0;
	linklist tmp = NULL;
	
	*head = (linklist)malloc(sizeof(lnode));
	(**head).next = NULL;
	(**head).data = -1;
	
	if(*head != NULL)
	{
		printf("Allocation succeeds\n");		

		for(i=0; i<size; i++)
		{
			tmp = (linklist)malloc(sizeof(lnode));
			if(tmp != NULL)
			{
				(*tmp).next = (*head);
				(*tmp).data = i;
			
				*head = tmp;
			}
		}
	}
}

Status insert(linklist *head,int i,ElemType e)
{
	int count = 0;
	linklist index = *head;
	linklist tmp = NULL;
	
	for(count = 0;count < i-1 && index != NULL; count++)
	{
		index = index->next;
	}
	
	tmp = (linklist)malloc(sizeof(lnode));
	(*tmp).next = NULL;
	(*tmp).data = e;

	tmp->next = index->next;
	index->next = tmp;
}

void print(int num)
{
	printf("%d ",num);
}

void traverse(linklist head,void (*func)())
{
	linklist index = head;
	
	while(index != NULL)
	{
		func((*index).data);
		index = index->next;
	}
	printf("\n");
}

void createHead(linklist *head,int size)
{
	int i = 0;
	linklist tmp = NULL;
	linklist index;

	*head = (linklist)malloc(sizeof(lnode));
	if((*head) != NULL)
	{
		printf("Allocation succeeds\n");
		
		(**head).next = NULL;
		(**head).data = -1;
		
		index = *head;
		
		for(i = 0; i < size; i++)
		{
			tmp = (linklist)malloc(sizeof(lnode));
			(*tmp).data = i;
			(*tmp).next = NULL;
	
			(*index).next = tmp;
			index = tmp;
		}
	}
}

void destroy(linklist *head)
{
	linklist index = *head;
	
	while(*head != NULL)
	{
		index = (**head).next;
		free(*head);
		*head = index;
	}
	printf("free succeeds\n");
}
