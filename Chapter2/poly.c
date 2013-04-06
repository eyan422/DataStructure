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
int LocElem(poly pointer, Elem dat,int (*func)(poly pointer,Elem dat),int *loc, char *funcName);
int compareBoth(poly pointer,Elem dat);
void createElem(Elem *dat, float c, int e);
void insertHead(poly pointer, Elem dat);
void insertTail(poly pointer, Elem dat);
Status OrderInsert(poly pointer,Elem e,int (*func)(poly, Elem));
int compareExpn(poly, Elem);
float sum(Elem,Elem);
void AddPolyn(poly pa, poly pb);
int cmp(int a, int b);
int GetExpn(poly p);
void inserBefore(poly pa, poly node);

int main()
{
	int result;
	poly p;
	poly b;
	Elem dat,dat1,dat2;

	createElem(&dat,0.0,0);
	createElem(&dat1,0.2,2);
	createElem(&dat2,0.3,3);
	
	create(&p);
	create(&b);
	//insertHead(p,dat1);
	//insertTail(p,dat2);
	OrderInsert(p,dat2,compareExpn);
	OrderInsert(p,dat1,compareExpn);
	traverse(p,print);
	LocElem(p, dat1, compareBoth,&result,"compareBoth");
		
	createElem(&dat2,0.1,2);
	OrderInsert(p,dat2,compareExpn);
	traverse(p,print);
	
	createElem(&dat2,-0.1,1);
	OrderInsert(p,dat2,compareExpn);
	traverse(p,print);	

	printf("---------------------------------------\n");
	createElem(&dat2,-0.3,2);
	OrderInsert(p,dat2,compareExpn);
	traverse(p,print);
	
	printf("---------------------------------------\n");
	createElem(&dat2,0.1,1);
	//createElem(&dat2,0.1,2);
	OrderInsert(b,dat2,compareExpn);
	traverse(b,print);
	printf("---------------------------------------\n");
	AddPolyn(p,b);
	traverse(p,print);
	printf("---------------------------------------\n");
	
	destroy(&p);
	destroy(&b);
	return OK;
}

int cmp(int a, int b)
{
	if(a == b)
	{
		return 0;
	}
	else if(a > b)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int GetExpn(poly p)
{
	if(p != NULL)
	{		
		return p->data.expn;
	}
}

void AddPolyn(poly pa, poly pb)
{
	poly qa = NULL;
	poly qb = NULL;
	poly tmp = NULL;
	poly prevA = NULL;
	//poly prevB = NULL;
	
	prevA = pa->next;
	qa = pa->next;
	qb = pb->next;
	
	int expnA = 0;
	int expnB = 0;	
				printf("=========\n");

	while(qa && qb)
	{
		expnA = GetExpn(qa);
		expnB = GetExpn(qb);
		
		switch( cmp(expnA,expnB) )
		{
			case -1:
				prevA = qa;
				qa = qa->next;
				break;
			case 0:	
				printf("=========\n");
				if( sum(qa->data,qb->data) != 0)
				{
					printf("!0\n");
					qa->data.coef += qb->data.coef; 
					prevA = qa;
					qa = qa->next;
				}
				else	
				{
					printf("0\n");
					print(prevA);
					printf("\n");
					print(qa);
					printf("\n");
					prevA->next = qa->next;
					prevA = qa;
					qa = qa->next;
					free(qa);	
				}
				qb = qb->next;
				break;
			case 1:
				tmp = (poly)malloc(sizeof(node));
				tmp->data.coef = qb->data.coef;
				tmp->data.expn = qb->data.expn;

				tmp->next = qa;				
				prevA->next = tmp;
		
				qb = qb->next;
				break;
		}
	}
}

float sum(Elem a,Elem b)
{
	if(a.expn == b.expn)
	{
		return (a.coef + b.coef);
	}
}

Status OrderInsert(poly pointer,Elem e,int (*func)(poly, Elem))
{
	int result = -1;
	int count = 0;
	poly prev = pointer;
	poly index = pointer;
	poly tmp = NULL;
	char *pclFunc = "OrderInsert";

	if(LocElem(index,e,func,&result,"compareExpn") == FALSE)
	{
		//printf("Not found\n");
		
		tmp = (poly)malloc(sizeof(node));
		tmp->data.coef = e.coef;
		tmp->data.expn = e.expn;
		
		while(index != NULL)
		{		
			if(e.expn < index->data.expn)
			{
				tmp->next = prev->next;
				prev->next = tmp;	
				return;
			}	
			prev = index;		
			index = index->next;
		}	
		insertTail(pointer,e);

		return FALSE;
	}	
	else
	{
		for(count = 0; count < result; count++)
		{
			prev = index;
			index = index->next;
		}		
		//print(prev);
		//print(index);
		
		if( sum(index->data,e) != 0)
		{
			index->data.coef += e.coef; 
		}
		else	
		{
			prev->next = index->next;
			free(index);	
		}
		//print(index);
		//printf("\n");
	}

	return TRUE;
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

int compareBoth(poly pointer,Elem dat)
{
	if(pointer->data.coef == dat.coef && pointer->data.expn == dat.expn)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int compareExpn(poly pointer,Elem dat)
{
	if(pointer->data.expn == dat.expn)
	{
		return 0;
	}
	else if(pointer->data.expn > dat.expn)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int LocElem(poly pointer, Elem dat,int (*func)(poly pointer,Elem dat),int *loc, char *funcName)
{
	int count = 0;
	*loc = -1;
	poly index = pointer;
	
	printf("%s\n",funcName);	

	while(index != NULL)
	{
		if(func(index,dat) == 0)
		{
			*loc = count;
			//printf("Found:the loc is <%d>\n",*loc);
			return TRUE;
		}
		index = index->next;
		count++;
	}
	return FALSE;
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

