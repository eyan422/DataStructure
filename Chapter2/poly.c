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
void compare(poly pointer,Elem dat);
void createElem(Elem *dat, float c, int e);

int main()
{
	int result;
	poly p;
	Elem dat;

	createElem(&dat,0.0,0);
	
	create(&p);
	traverse(p,print);
	LocElem(p, dat, &result);
	destroy(&p);
	return OK;
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
		if(compare(pointer,dat) == TRUE)
		{
			*loc = count;
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
		func(pointer);
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
