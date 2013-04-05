#include <Common.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	float 	coef;
	int 	expn;
}ElemType;

typedef struct
{
	ElemType data;
	struct node *next;
}node,*LinkList;

typedef LinkList polynomial;

void CreatePolyn(polynomial *pointer, int m);
void DestroyPolyn(polynomial *pointer);
void Traverse(polynomial pointer, void (*func)());
void printPoly(polynomial pointer);

int main()
{	
	polynomial p;
	p = (polynomial)malloc(sizeof(node));
	(*p).data.coef = 2.0;
	(*p).data.expn = 3;

	//ElemType b = p->data;
	//b.expn = 2;
	
	
	printf("%.1fX^%d ",(*p).data.coef,(*p).data.expn);
	//printf("%d ",b.expn);
	
	//CreatePolyn(&p,2);
	//Traverse(p,printPoly);
	//DestroyPolyn(&p);
	return OK;
}

void printPoly(polynomial pointer)
{
	printf("%fX^%d ",(pointer->data).coef,(pointer->data).expn);
}

void Traverse(polynomial pointer, void (*func)())
{
	polynomial index = pointer->next;
	
	while(index != NULL)
	{
		//func(pointer);
		//index = index->next;
	}
}

void CreatePolyn(polynomial *pointer, int m)
{
	int count = m;
	float coef;
	int expn;
	polynomial index = *pointer;
	polynomial tmp = NULL;
	
		
	index = (polynomial)malloc(sizeof(node));
	if(index != NULL)
	{
		index->next = NULL;
		(index->data).coef = 0;
		(index->data).expn = 0;
	}

	for(count = 0; count < m; count++)
	{
		tmp = (polynomial)malloc(sizeof(node));
		if(tmp != NULL)
		{
			printf("please input the coef:\n");
			scanf("%f",&coef);
			printf("please input the expn:\n");
			scanf("%d",&expn);

			tmp->next = index->next;
			index->next = tmp;
			//index = tmp;
		
			(tmp->data).coef = coef;
			(tmp->data).expn = expn;
		}
	}
	printf("Create succeeds\n");
}


void DestroyPolyn(polynomial *pointer)
{
	polynomial tmp = NULL;
	polynomial index = *pointer;

	while(index != NULL)
	{
		tmp = index->next;
		free(index);
		index = tmp;
	}
	
	printf("free succeeds\n");
}
