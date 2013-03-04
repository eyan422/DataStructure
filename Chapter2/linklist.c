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
Status insert(linklist *head,int i,ElemType);

int main()
{
	linklist head;
	createHead(&head,5);
	traverse(head,print);

	insert(&head,2,9);	
	traverse(head,print);
	destroy(&head);
	
	linklist tail;
	createTail(&tail,5);
	insert(&tail,2,12);
	traverse(tail,print);
	destroy(&tail);
	return OK;
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
	
	while((**head).next != NULL)
	{
		index = (**head).next;
		free(*head);
		*head = index;
	}
	printf("free succeeds\n");
}
