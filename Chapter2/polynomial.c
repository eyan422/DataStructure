#include <Common.h>

typedef struct term
{
	float ceof;
	int expn;
}term,Elem;

typedef struct pnode
{
	Elem data;
	struct pnode *next;
}pnode,*linklist;

typedef linklist polynomail;

Status CreatePolyn(polynomail *p,int ceof,int expn);
Status DestroyPolyn(polynomail *head)
void traverse(polynomail head,void (*func)());
void print(polynomail head);

int main()
{
	polynomail head;
	CreatePolyn(&head,0,0);
	DestroyPolyn(&head);	
	return OK;
}

void print(polynomail head)
{

}

void traverse(polynomail head,void (*func)())
{
	polynomail index = head;
	
	while(index != NULL)
	{
		func(index);
		index = index->next;
	}
}

Status CreatePolyn(polynomail *p,int ceof,int expn)
{
	polynomail index = *p;
	
	index = (polynomail)malloc(sizeof(pnode));
	if(index != NULL)
	{
		index->next = NULL;
		(index->data).ceof = ceof;
		(index->data).expn = expn;
	
		return OK;
	}
	return ERROR;
}


Status DestroyPolyn(polynomail *head)
{
	polynmail index = head;
	polynmail tmp = head;

	while(index != NULL)
	{
		tmp = index->next;
		free(index);
		index = tmp;
	}
}
