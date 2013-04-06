#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Common.h>

typedef struct
{
	float coef;
	int expn;
}Elem;

typedef struct
{
	Elem data;
	struct node *next;
}node,*linklist;

typedef linklist poly;

void create(poly *pointer);
void destroy(poly *pointer);
void print(poly pointer);
void traverse(poly pointer, void (*func)());
void LocElem(poly pointer, Elem dat, int *loc);
int compare(poly pointer,Elem dat);
void createElem(Elem *dat, float c, int e);
void insertHead(poly pointer, Elem dat);
void insertTail(poly pointer, Elem dat);

int main()
{
	int result;
	poly p;
	Elem dat,dat1,dat2;

	createElem(&dat,0.0,0);
	createElem(&dat1,0.2,2);
	createElem(&dat2,0.3,3);
	
	create(&p);
	insertHead(p,dat1);
	insertTail(p,dat2);
	traverse(p,print);
	LocElem(p, dat, &result);
	destroy(&p);
	return OK;
}

void insertHead(poly pointer, Elem dat)
{
	poly tmp = NULL;
	
	tmp = (poly)malloc(sizeof(node));

	if(tmp != NULL)
	{
		tmp->data.coef = dat.coef;
		tmp->data.expn = dat.expn;		

		tmp->next = pointer->next;
		pointer->next = tmp;
	}
	
}

void insertTail(poly pointer, Elem dat)
{
	poly index = pointer;
	poly tmp = NULL;
	
	tmp = (poly)malloc(sizeof(node));

	if(tmp != NULL)
	{
		tmp->data.coef = dat.coef;
		tmp->data.expn = dat.expn;
	
		while(index->next != NULL)
		{
			index = index->next;
		}
			
		index->next = tmp;
		tmp->next = NULL;
	}
}

void createElem(Elem *dat, float c, int e)
{
	dat->coef = c;
	dat->expn = e;
}

int compare(poly pointer,Elem dat)
{
	if(pointer->data.coef == dat.coef && pointer->data.expn == dat.expn)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void LocElem(poly pointer, Elem dat, int *loc)
{
	int count = 0;
	poly index = pointer;
	
	while(index != NULL)
	{
		if(compare(index,dat) == TRUE)
		{
			*loc = count;
			printf("Found:the loc is <%d>\n",*loc);
		}
		index = index->next;
		count++;
	}
}

void traverse(poly pointer, void (*func)())
{
	poly index = pointer;
	
	while(index != NULL)
	{
		func(index);
		printf("\n");
		index = index->next;
	}
}

void print(poly pointer)
{
	poly index = pointer;
	
	printf("%fX^%d ",index->data.coef,index->data.expn);
}

void create(poly *pointer)
{
	poly index = NULL;

	*pointer = (poly)malloc(sizeof(node));

	if(*pointer != NULL)
	{
		index = *pointer;
		index->next = NULL;
		index->data.coef = 0;
		index->data.expn = 0;
	}
}

void destroy(poly *pointer)
{
	poly index = *pointer;
	poly tmp = NULL;
	
	while(index != NULL)
	{
		free(index);
		tmp = index->next;
		index = tmp;
	}
}
