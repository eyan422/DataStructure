#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Common.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;
typedef SElemType OperandType;

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

OperandType EvaluateExpression();
char Precede(char Optr1, char Optr2,char array[][7]);

enum{plus,minus,multi,division,leftBracket,rightBracket,poundSign};

void TestSign(int Sign);
void PrintOptrRel(char array[][7]);

char OptrRange[7] = "+-*/()#";

int ConvertSign(char Sign);

char OptrRel[7][7] =	
{
	'>','>','<','<','<','>','>',
	'>','>','<','<','<','>','>',
	'>','>','>','>','<','>','>',
	'>','>','>','>','<','>','>',
	'<','<','<','<','<','=','%',
	'>','>','>','>','%','>','>',
	'<','<','<','<','<','%','=',
};

#define TEST

int main()
{
	SqStack OPTR;
	SqStack OPND;
	
	#ifdef TEST
		PrintOptrRel(OptrRel);
		TestSign(plus);
		TestSign(poundSign);

		printf("\n");
		Precede('+','*',OptrRel);
	#endif
	
	//EvaluateExpression();
	/*
	int j;
  	SqStack s;
  	
	SElemType e;
  	InitStack(&s);
  	
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
	
	//DestroyStack(&s);
}

int ConvertSign(char Sign)
{
	int result = -1;
	char pclTmp[2];
	
	memset(pclTmp,0,sizeof(pclTmp));

	pclTmp[0] = Sign;
	//printf("pclTmp[%s]\n",pclTmp);
	
	if(strstr(OptrRange,pclTmp) == NULL)
	{
		printf("[%s] is not in the range[%s]\n",pclTmp,OptrRange);
		return ERROR;
	}
	else
	{
		switch(Sign)
		{
			case '+':
				result = plus;
				break;
			case '-':
				result = minus;
				break;
			case '*':
				result = multi;
				break;
			case '/':
				result = division;
				break;
			case '(':
				result = leftBracket;
				break;
			case ')':
				result = rightBracket;
				break;
			case '#':
				result = poundSign;
				break;
			default:
				result = -1;
		}
	}
	return result;
}

char Precede(char Optr1, char Optr2, char array[][7])
{
	int ilOptr1 = -1;
	int ilOptr2 = -1;

	printf("Optr1<%c>,cOptr2<%c>\n",Optr1,Optr2);
	
	ilOptr1 = ConvertSign(Optr1);
	ilOptr2 = ConvertSign(Optr2);

	if(ilOptr1 < 0 || ilOptr2 < 0)
	{
		printf("invalid Optr\n");
		return ERROR;
	}
	
	printf("ilOptr1<%d>,ilOptr2<%d>\nResult[%c]\n",ilOptr1,ilOptr2,array[ilOptr1][ilOptr2]);
	
	return array[ilOptr1][ilOptr2];
}

void PrintOptrRel(char array[][7])
{
	int ilCol = 0;
	int ilRow = 0;
	
	for(ilRow = plus; ilRow <= poundSign; ilRow++)
	{
		for(ilCol = plus; ilCol <= poundSign; ilCol++)
		{
			printf("[%c] ",array[ilRow][ilCol]);
		}
		printf("\n");
	}
}

void TestSign(int Sign)
{
		printf("Sign<%d>",Sign);
}

/*
OperandType EvaluateExpression()
{
	char c = '\0';
	char x = '\0';

	InitStack(OPTR);
	Push(OPTR,'#');

	InitStack(OPND);
	c = getchar();
	
	while(c != '#' || GetTop(OPTR) != '#')
	{
		if( !In(c,OP))
		{
			Push(OPND,c);
			c = getchar();
		}
		else
		{
			switch(Precede(GetTop(OPTR),c))
			{
				case '<':
					Push(OPTR,c);
					c = getchar();
					break;
				case '=':
					Pop(OPTR,x);	
					c = getchar();
					break;
				case '>':
					Pop(OPTR,theta);
					Pop(OPND,b);
					Pop(OPND,a);
					Push(OPND,Operate(a,theta,b));
					break;
				default:
					exit(OVERFLOW);
					break;
			}
		}
	}
	return GetTop(OPND);
}
*/

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

