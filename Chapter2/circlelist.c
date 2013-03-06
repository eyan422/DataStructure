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

int main()
{
	clinkedlist head = NULL;
	
	create(&head);
	destroy(&head);
	
	return OK;
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
	clinkedlist index = *head;
	
	if(*head != NULL)
	{
		while((*head)->next != *head)
		{	
			index = (*head)->next;
			free(*head);
			*head = index;
		}
		free(*head);
		printf("%s free succeeds\n",pclFunc);
	}
	else
	{
		printf("%s *head is NULL\n",pclFunc);
		return ERROR;
	}
	return OK;
}
