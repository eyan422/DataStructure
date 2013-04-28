#include <stdio.h>
#include <stdlib.h>
#include <Common.h>

#define MAXQSIZE 100

typedef int QElemType;

typedef struct
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue *Q);
Status DestroyQueue(SqQueue *Q);
int QueueLength(SqQueue Q);
Status EnQueue(SqQueue *Q, QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);
void TraverseQueue(SqQueue Q,void (*func)(QElemType));
void print(QElemType e);

int main()
{
	SqQueue Q;
	QElemType result;
	
	InitQueue(&Q);
	EnQueue(&Q,5);
	EnQueue(&Q,6);
	EnQueue(&Q,7);
	TraverseQueue(Q,print);

	printf("\n-----------\n");	

	DeQueue(&Q,&result);
	TraverseQueue(Q,print);

	printf("\n-----------\n");	
	
	DestroyQueue(&Q);

	return 0;
}

Status InitQueue(SqQueue *Q)
{
	Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	
	if(Q->base == NULL)
	{
		exit(OVERFLOW);
	}

	Q->front = Q->rear = 0;
	
	return OK;
}

Status DestroyQueue(SqQueue *Q)
{
	free(Q->base);
}

int QueueLength(SqQueue Q)
{
	return (Q.front - Q.rear + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue *Q, QElemType e)
{
	if((Q->rear + 1) % MAXQSIZE == Q->front)
	{
		return ERROR;
	}
	
	Q->base[Q->rear] = e;
	
	Q->rear = (Q->rear + 1) % MAXQSIZE;

	return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e)
{
	if(Q->front == Q->rear)
	{
		exit(OVERFLOW);
	}

	e = (Q->base[Q->front]);

	Q->front = (Q->front + 1) % MAXQSIZE;

	return OK;
}
	
void TraverseQueue(SqQueue Q,void (*func)(QElemType))
{
	int index = Q.front;

	while(index != Q.rear+1)
	{
		func(Q.base[index]);
		index++;
	}
}

void print(QElemType e)
{
	printf("%d ",e);
}	
