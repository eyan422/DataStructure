#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Common.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;
typedef SElemType OperandType;

/*
typedef struct
{
	SElemType *base;
	SElemType *top;

	int stacksize;
}EqStack, *EpStack;
*/

typedef struct
{
	SElemType *base;
	SElemType *top;

	int stacksize;
}SqStack, *pStack;

Status InitStack(pStack S);

Status GetTop(SqStack S, SElemType *e);
char GetTop1(SqStack S);
void DestroyStack(pStack S);

void ClearStack(pStack S);

Status StackEmpty(pStack S);

int StackLength(pStack S);

void Push(pStack S, SElemType e);
Status Pop(pStack S, SElemType *e);
void StackTraverse(SqStack S, void (*visit)(SElemType));
void print(SElemType c);

//OperandType EvaluateExpression();
OperandType EvaluateExpression(pStack OPTR, pStack OPND);
char Precede(char Optr1, char Optr2,char array[][7]);

enum{plus,minus,multi,division,leftBracket,rightBracket,poundSign};

void TestSign(int Sign);
void PrintOptrRel(char array[][7]);

char OptrRange[7] = "+-*/()#";

int ConvertSign(char Sign);
int CheckOptr(char Sign);
int Operate(char opnd1, char optr, char opnd2);

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

//#define TEST

char Expression[100] = "3*(7-2)#";

int main()
{
	SqStack OPTR;
	SqStack OPND;

	//InitStack(&OPTR);
	//InitStack(&OPND);
	
	#ifdef TEST
		PrintOptrRel(OptrRel);
		TestSign(plus);
		TestSign(poundSign);

		printf("\n");
		Precede('+','*',OptrRel);
	#endif
	
	EvaluateExpression(&OPTR,&OPND);
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
	
	//DestroyStack(&OPTR);
	//DestroyStack(&OPND);
}

int CheckOptr(char Sign)
{
	char pclTmp[2];
	
	memset(pclTmp,0,sizeof(pclTmp));
	pclTmp[0] = Sign;
	
	if(strstr(OptrRange,pclTmp) == NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int ConvertSign(char Sign)
{
	int result = -1;
	
	
	if(CheckOptr(Sign) == FALSE)
	{
		printf("[%c] is not in the range[%s]\n",Sign,OptrRange);
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

	printf("Optr1[%c],Optr2[%c]\n",Optr1,Optr2);
	
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


OperandType EvaluateExpression(pStack OPTR, pStack OPND)
{
	char c = '\0';
	char x = '\0';
	int ilCount = 0;
	
	char a,b,theta;

	SElemType e;
	
	InitStack(OPTR);
	Push(OPTR,'#');

	InitStack(OPND);
	c = Expression[ilCount++];

	while(c != '#' ||  GetTop1(*OPTR) != '#')
	{
		if( !CheckOptr(c) )
		{
			Push(OPND,c);
			c = Expression[ilCount++];
		}
		else
		{
			switch(Precede(GetTop1(*OPTR),c,OptrRel))
			{
				case '<':
					Push(OPTR,c);
					//c = getchar();
					c = Expression[ilCount++];
					break;
				case '=':
					Pop(OPTR,&x);
					printf("x<%c>\n",x);
					if(x == '#')
					{
						c == x;
					}
					//c = getchar();
					c = Expression[ilCount++];
					break;
				case '>':
					Pop(OPTR,&theta);
					printf("theta[%c]\n",theta);
					Pop(OPND,&b);
					printf("b[%c]\n",b);
					Pop(OPND,&a);
					printf("a[%c]\n",a);
					Push(OPND,Operate(a,theta,b));
					break;
				default:
					exit(OVERFLOW);
					break;
			}
		}
	}
	printf("Final Result is <%c>\n",GetTop1(*OPND));
	return GetTop1(*OPND);
}

int Operate(char opnd1, char optr, char opnd2)
{
	int ilResult = 0;
	int ilOpnd1 = opnd1 - '0'; 
	int ilOpnd2 = opnd2 - '0';

	switch(optr)
	{
		case '+':
			ilResult = ilOpnd1 + ilOpnd2;
			break;
		case '-':
			ilResult = ilOpnd1 - ilOpnd2;
			break;
		case '*':
			ilResult = ilOpnd1 * ilOpnd2;
			break;
		case '/':
			ilResult = ilOpnd1 / ilOpnd2;
			break;
		default:
			printf("invalid optr\n");
			break;
	}	 
	
	printf("ilResult[%d]\n",ilResult);
	
	return ilResult + '0';
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

char GetTop1(SqStack S)
{
	if(S.top == S.base)
	{
		return ERROR;
	}
	
	return *(S.top-1);
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

