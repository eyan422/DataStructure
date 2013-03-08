#include <Common.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct lnode
{
	ElemType data;
	struct clnode *next;
}clnode,*clinkedlist;

Status create(clinkedlist *head);
Status destroy(clinkedlist *head);
void insertTail(clinkedlist head,ElemType e);
void deleteTail(clinkedlist head,ElemType *e);
void traverse(clinkedlist head,void (*func)());
void print(ElemType e);
int ListLength(clinkedlist head);
Status insert(clinkedlist head,int i,ElemType e);
Status delete(clinkedlist head,int i,ElemType *e);

int main()
{
	ElemType result;
	clinkedlist head = NULL;
	
	create(&head);
	insertTail(head,5);
	insertTail(head,6);
	insertTail(head,7);
	traverse(head,print);
	printf("\n");
	ListLength(head);
	deleteTail(head,&result);
	traverse(head,print);
	printf("\n");
	ListLength(head);
	
	insert(head,1,11);
	traverse(head,print);
	printf("\n");
	destroy(&head);
	
	return OK;
}

Status insert(clinkedlist head,int i,ElemType e)
{
	int count = 0;
	char *pclFunc = "insert";

	clinkedlist index = head->next;
	clinkedlist prev = head->next;
	clinkedlist tmp = NULL;
	
	if(i < 0 || i > ListLength(head) - 1)
	{
		printf("%s The i<%d> is not in the range[0-%d]\n",ListLength(head)-1);
		return ERROR;
	}
	
	for(count = 0; count < i; count++)
	{
		prev = index;
		index = index->next;
	}
	
	tmp = (clinkedlist)malloc(sizeof(clnode));
	tmp->data = e;
	tmp->next = index;
	prev->next = tmp;
}

Status delete(clinkedlist head,int i,ElemType *e)
{

}

int ListLength(clinkedlist head)
{
	int length = 0;
	char *pclFunc = "ListLength";

	clinkedlist index = head;
	
	while(index->next != head)
	{
		index = index->next;
		length++;
	}
	printf("%s The length is <%d>\n",pclFunc,length);
}

void deleteTail(clinkedlist head,ElemType *e)
{
	char *pclFunc = "deleteTail";

	clinkedlist index = head;
	clinkedlist prev = head;
	
	while(index->next != head)
	{
		prev = index;
		index = index->next;
	}
	prev->next = index->next;
	*e = index->data;
	printf("%s The deleted element is <%d>\n",pclFunc,*e);
	free(index);
}

void print(ElemType e)
{
	printf("%d ",e);
}

void traverse(clinkedlist head,void(*func)())
{
	clinkedlist index = head->next;
	if(head != NULL)
	{
		while(index != head)
		{
			func(index->data);
			index = index->next;
		}
	}
}

void insertTail(clinkedlist head,ElemType e)
{
	clinkedlist index = head;
	clinkedlist tmp = NULL;
	
	if(head != NULL)
	{
		while(index->next != head)
		{
			index = index->next;
		}	
		tmp = (clinkedlist)malloc(sizeof(clnode));
		tmp->data = e;
		if(tmp != NULL)
		{
			tmp->next = index->next;
			index->next = tmp;
		}
	}
}


Status create(clinkedlist *head)
{
	char *pclFunc = "create";
	
	*head = (clinkedlist)malloc(sizeof(clnode));
	if((*head) == NULL)
	{
		printf("%s Allocation fails\n",pclFunc);
		return ERROR;
	}
	else
	{
		printf("%s Allocation succeeds\n",pclFunc);
		(*head)->next = *head;
		(*head)->data = 0;
		return OK;
	}
}

Status destroy(clinkedlist *head)
{
	char *pclFunc = "destroy";
	clinkedlist index = (*head)->next;
	clinkedlist tmp = NULL;
	
	if(*head != NULL)
	{
		while(index != *head)
		{	
			tmp = index->next;
			free(index);
			index = tmp;
		}
		free(index);
		printf("%s free succeeds\n",pclFunc);
	}
	else
	{
		printf("%s *head is NULL\n",pclFunc);
		return ERROR;
	}
	return OK;
}
