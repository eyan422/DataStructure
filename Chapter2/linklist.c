#include <Common.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct
{
	ElemType data;
	struct lnode *next;
}lnode,*linklist;

void create(linklist head,int size);
void destroy(linklist head);

int main()
{
	lnode head;
	create(&head,5);
	//destroy(head);
	return OK;
}

void destroy(lnode *head)
{
	linklist index = head;

	if(head == NULL)
	{
		printf("linklist is null\n");
		exit(ERROR);
	}

	if( head->next == NULL)
	{
		free(head);
	}
	else
	{
		while( head->next != NULL )
		{
			index = (linklist)(head->next);
			free(head);
			head = index;
		}
		free(head);
		head = NULL;
		index = NULL;
	}	
}

void create(lnode *head,int size)
{
	int i = 0;
	lnode *tmp = NULL;
	lnode *index = head;

	head = (lnode *)malloc(sizeof(lnode));
	(*head).next = NULL;
	(*head).data = 0;
	
	for(i = 0; i < size; i++)
	{
		tmp = (linklist)malloc(sizeof(lnode));
		(*tmp).data = i;
		(*tmp).next = NULL;
	
		(*index).next = (lnode *)tmp;
		index = tmp;
	}
}
