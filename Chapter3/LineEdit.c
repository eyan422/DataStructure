#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Common.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

//typedef int SElemType;
typedef char SElemType;

typedef struct
{
	SElemType *base;
	SElemType *top;

	int stacksize;
}SqStack,* pStack;

Status InitStack(pStack S);

Status GetTop(SqStack S, SElemType *e);
void DestroyStack(pStack S);

void ClearStack(pStack S);

Status StackEmpty(pStack S);

int StackLength(pStack S);

void Push(pStack S, SElemType e);
Status Pop(pStack S, SElemType *e);
void StackTraverse(SqStack S, void (*visit)(SElemType));
void print(SElemType c);
void LineEdit(SqStack S);

int main()
{
	int j;
  	SqStack s;
  	
	SElemType e;
  	InitStack(&s);
 	
	/* 	
	for(j=1;j<=12;j++)
    	{
		Push(&s,j);
	}
	
	StackTraverse(s,print);
  	Pop(&s,&e);
	
	StackTraverse(s,print);
	//GetTop(s,&e);
	
	//conversion(s);
	*/
	LineEdit(s);
	
	DestroyStack(&s);
}

void LineEdit(SqStack S)
{
	char ch = '\0';
	char clTop = '\0';

	ch = getchar();	

	while(ch != EOF)
	{
		//while(ch != EOF && ch != '\n')
		//if(ch != EOF && ch != '\n')
		if(ch != '\n')
		{
			switch(ch)
			{	
				case '#': Pop(&S,&clTop);
					break;
				case '@': ClearStack(&S);
					break;
				default : Push(&S,ch);
					break;
				
			}	
		}
		ch = getchar();
	}

	StackTraverse(S,print);	

	ClearStack(&S);
	if(ch != EOF)
	{
		ch = getchar();
	}
}

int StackLength(pStack S)
{
	return S->top - S->base;
}

void Push(pStack S, SElemType e)
{
	if(S->top - S->base >= S->stacksize)
	{
		S->base = (SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));

		if(S->base == NULL)
		{
			exit(OVERFLOW);
		}
	
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	
	*(S->top)++ = e;
}

Status StackEmpty(pStack S)
{
	if(S->base == S->top)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void ClearStack(pStack S)
{
	S->top = S->base;
}

void DestroyStack(pStack S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;
}

Status GetTop(SqStack S, SElemType *e)
{
	if(S.top == S.base)
	{
		return ERROR;
	}
	
	*e = *(S.top-1);
	
	return OK;
}

Status InitStack(pStack S)
{
	S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	
	if(S->base == NULL)
	{
		exit(OVERFLOW);
	}

	S->top = S->base;
	
	S->stacksize = STACK_INIT_SIZE;

	return OK;
}

void StackTraverse(SqStack S, void (*visit)(SElemType))
{
	while(S.top > S.base)
	{
		visit(*S.base++);
	}
	printf("\n");
}

void print(SElemType c)
{
	printf("%c ",c);
}

Status Pop(pStack S, SElemType *e)
{
	if(S->base == S->top)
	{
		return ERROR;
	}
	
	*e = *--(S->top);
	
	return OK;
}

