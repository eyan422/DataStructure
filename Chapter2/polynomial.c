#include <Common.h>

typedef struct dat
{
	int e;
	int b;
}ElemType;

typedef struct node
{
	ElemType data;
	struct node *next;
}node,*ListPointer;

Status create();

int main()
{
	
	return OK;
}
