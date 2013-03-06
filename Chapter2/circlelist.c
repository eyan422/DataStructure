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
void insertTail(clinkedlist head,ElemType);
void traverse(clinkedlist head,void (*func)());
void print(ElemType e);

int main()
{
	clinkedlist head = NULL;
	
	create(&head);
	insertTail(head,5);
	traverse(head,print);
	destroy(&head);
	
	return OK;
}

void print(ElemType e)
{
	printf("ElemType<%d>\n",e);
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
