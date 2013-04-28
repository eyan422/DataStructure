#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Common.h>

#define QUEUE_INIT_SIZE 100
#define QUEUEINCREMENT 10

typedef int QElemType;

typedef struct QNode
{
	QElemType data;
	struct Qnode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue *Q);
Status DestroyQueue(LinkQueue *Q);
Status EnQueue(LinkQueue *Q,QElemType e);
Status DeQueue(LinkQueue *Q, QElemType *e);
Status TranverseQueue(LinkQueue Q, void (*func)(QElemType elem));
void print(QElemType elem);

int main()
{
	LinkQueue Q;
	QElemType e = 5;

	InitQueue(&Q);

	EnQueue(&Q,e);
	TranverseQueue(Q,print);
	
	printf("\n------------\n");
	
	e = 6;
	EnQueue(&Q,e);
	TranverseQueue(Q,print);
	
	printf("\n------------\n");
	
	e = 7;
	EnQueue(&Q,e);
	TranverseQueue(Q,print);
	
	printf("\n------------\n");
	DeQueue(&Q,&e);
	TranverseQueue(Q,print);
	
	DestroyQueue(&Q);	
	
	return 0;
}

Status InitQueue(LinkQueue *Q)
{	
	Q->front = (QueuePtr)malloc(QUEUE_INIT_SIZE * sizeof(QElemType));

	if(Q->front == NULL)
	{
		exit(OVERFLOW);
	}
	
	Q->front->next = NULL;	
	
	Q->rear = Q->front;
}

Status DestroyQueue(LinkQueue *Q)
{
	while(Q->front)
	{
		Q->rear = (QueuePtr)(Q->front->next);
		free(Q->front);
		Q->front = Q->rear;
	}
	
	return OK;
}

Status EnQueue(LinkQueue *Q,QElemType e)
{
	QueuePtr tmp = NULL;
	
	tmp = (QueuePtr)malloc(sizeof(QElemType));

	if(tmp == NULL)
	{
		exit(OVERFLOW);
	}	

	tmp->data = e;
	tmp->next = NULL;
	Q->rear->next = tmp;
	Q->rear = tmp;
	
	return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e)
{
	if(Q->front == Q->rear)
	{
		return ERROR;
	}

	QueuePtr tmp = (QueuePtr)Q->front->next;
	
	*e = tmp->data;

	Q->front->next = tmp->next;
	
	if(Q->rear == tmp)
	{
		Q->rear = Q->front;
	}	
	
	free(tmp);

	return OK;
}

void print(QElemType elem)
{
	printf("Elem<%d>\n",elem);
}

Status TranverseQueue(LinkQueue Q, void (*func)(QElemType elem))
{
	QueuePtr index = Q.front->next;
	while(index != NULL)
	{
		func(index->data);
		index = (QueuePtr)index->next;
	}
}
