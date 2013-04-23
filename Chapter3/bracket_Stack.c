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
Status BracketPairCheck(SqStack S,char *String);

#define SIZE 100
char pcgBracket[10] = "[]{}()";
Status pairup(char,char);

int main()
{
	int j;
	char *clBracket;
  	SqStack s;

	clBracket = (char *)malloc(SIZE * sizeof(char));
	if(clBracket == NULL)
	{
		exit(OVERFLOW);
	} 
	
	printf("Please input the brcket string:\n");
	scanf("%s",clBracket);  	
	printf("The string: %s\n",clBracket);
	
	//SElemType e;
  	InitStack(&s);

	BracketPairCheck(s,clBracket);
	
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
	DestroyStack(&s);
}

Status BracketPairCheck(SqStack S,char *String)
{
	int ilLen = 0;
	int ilCount = 0;
	char clTop = '\0';
	char clPop = '\0';
	char pclTmp[2] = "\0";
	char *pclFunc = "BracketPairCheck";
	
	//printf("%s The length of %s is <%d>\n",pclFunc,String,(int)strlen(String));

	for(ilCount = 0; ilCount < strlen(String); ilCount++)
	{
		//printf("char %c\n",String[ilCount]);
		
		if(isdigit(String[ilCount]) || isalpha(String[ilCount]))
		{
			printf("Either digit or alpha,String[%d]<%c>\n",ilCount,String[ilCount]);
			continue;
		}
		else
		{	
			pclTmp[0] = String[ilCount];
			if(strstr(pcgBracket,pclTmp) != 0)
			{
				printf("Neither digit nor alpha, String[%d]<%c>\n",ilCount,String[ilCount]);
				if(ilCount == 0 || StackEmpty(&S) != FALSE) 
				{
					//printf("count == 0\n");
					Push(&S,String[ilCount]);
				}
				else
				{	
					if(GetTop(S,&clTop) != ERROR)
					{
						printf("Stack Top Element: %c\n",clTop);
						
						if(pairup(clTop,String[ilCount]) == TRUE)
						{
							Pop(&S,&clPop);
							printf("Pair up: clTop<%c>String[ilCount]<%c>\n",clTop,String[ilCount]);
						}
						else
						{
							Push(&S,String[ilCount]);
						}
					}
				}
			}
		}
	}
	
	if(StackEmpty(&S) == FALSE)
	{
		printf("Pair up incomplete,the rest is :\n");
		StackTraverse(S,print);	
	}
	else
	{
		printf("Pair up complete\n");
	}

	return OK;
}

Status pairup(char clTop, char clNew)
{
	switch(clTop)
	{
		case '[':
			if(clNew == ']')
			{
				return TRUE;
			}
			break;
		//case ']':
		//	break;
		case '(':
			if(clNew == ')')
			{
				return TRUE;
			}
			break;
		//case ')':
		//	break;
		case '{':
			if(clNew == '}')
			{
				return TRUE;
			}
			break;
		//case '}':
		//	break;
		default:
			return FALSE;
			break;
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
	printf("%d ",c);
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

