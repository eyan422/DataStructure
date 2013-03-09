#include <Common.h>

typedef struct dlnode
{
	ElemType data;
	struct dlnode *next;
	struct dlnode *prev;
}dlnode,*DoubleLinkedList;

Status create(DoubleLinkedList *head);
Status destroy(DoubleLinkedList *head);
Status insertTail(DoubleLinkedList head,ElemType e);
Status deleteTail(DoubleLinkedList head,ElemType *e);
//Status insertHead(DoubleLinkedList head,ElemType e);
//Status deleteHead(DoubleLinkedList head,ElemType *e);
void print(ElemType data);
void traverse_next(DoubleLinkedList head,void (*func)());
void traverse_prev(DoubleLinkedList head,void (*func)());

int main()
{
	ElemType result = 0;
	DoubleLinkedList head = NULL;

	create(&head);
	insertTail(head,1);
	insertTail(head,2);
	insertTail(head,3);
	insertTail(head,4);
	traverse_next(head,print);
	traverse_prev(head,print);

	deleteTail(head,&result);
	traverse_next(head,print);
	traverse_prev(head,print);

	destroy(&head);
	return OK;
}

Status deleteTail(DoubleLinkedList head,ElemType *e)
{
	DoubleLinkedList index = head->prev;
	
	index->prev->next = index->next;
	index->next->prev = index->prev;
	*e = index->data;
	free(index);
	
	printf("The delete element is <%d>\n",*e);
	
	return OK;	
}

Status insertTail(DoubleLinkedList head,ElemType e)
{
	DoubleLinkedList index = head;
	DoubleLinkedList tmp = NULL;
	
	tmp = (DoubleLinkedList)malloc(sizeof(dlnode));
	if(tmp != NULL)
	{
		tmp->data = e;
		
		tmp->prev = index->prev;
		index->prev->next = tmp;
		tmp->next = index;
		index->prev = tmp;
	}
}

Status create(DoubleLinkedList *head)
{
	*head = (DoubleLinkedList)malloc(sizeof(dlnode));
	if(*head != NULL)
	{
		(*head)->next = *head;
		(*head)->prev = *head;
		(*head)->data = 0;
		
		return OK;
	}
	return ERROR;
}

Status destroy(DoubleLinkedList *head)
{
	DoubleLinkedList index = (*head)->next;
	DoubleLinkedList tmp = index;
	
	if(*head != NULL)
	{
		while(index != *head)
		{
			tmp = index->next;
			free(index);
			index = tmp;		
		}
		free(*head);
	}
}

void print(ElemType data)
{
	printf("%d ",data);
}

void traverse_prev(DoubleLinkedList head,void (*func)())
{

	DoubleLinkedList index = head->prev;
	
	if(head != NULL)
	{
		while(index != head)
		{
			func(index->data);
			index = index->prev;
		}
		printf("\n");
	}
}

void traverse_next(DoubleLinkedList head,void (*func)())
{
	DoubleLinkedList index = head->next;
	
	if(head != NULL)
	{
		while(index != head)
		{
			func(index->data);
			index = index->next;
		}
		printf("\n");
	}
}
