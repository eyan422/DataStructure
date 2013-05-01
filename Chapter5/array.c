#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <Common.h>

#define MAX_ARRAY_DIM 8

typedef int ElemType;

typedef struct
{
	ElemType *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

Status InitArray(Array *A, int dim, ...);
Status DestroyArray(Array *A);
Status Locate(Array A, va_list ap, int *off);
Status Value(Array A, ElemType *e, ...);
Status Assign(Array *A, ElemType e,...);

int main()
{

	return 0;
}

Status InitArray(Array *A, int dim, ...)
{
	int i;
	int elemtotal;
	va_list ap;
	
	if(dim < 1 || dim > MAX_ARRAY_DIM)
	{
		return ERROR;
	}

	A->dim = dim;
	
	A->bounds = (int *)malloc(dim * sizeof(int));

	if(A->bounds == NULL)
	{
		exit(OVERFLOW);
	}
	
	elemtotal = 1;

	va_start(ap,dim);
	for(i = 0; i < dim; ++i)
	{
		A->bounds[i] = va_arg(ap,int);
		if(A->bounds[i] < 0)
		{
			return ERROR;
		}
		elemtotal *= A->bounds[i];
	}
	
	va_end(ap);
	
	A->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	
	if(A->base == NULL)
	{
		exit(OVERFLOW);
	}
	
	A->constants = (int *)malloc(dim * sizeof(int));
	
	if(A->constants == NULL)
	{
		exit(OVERFLOW);
	}
	
	A->constants[dim-1] = 1;

	for(i = dim -2; i>=0; --i)
	{
		A->constants[i] = A->bounds[i+1] * A->constants[i+1];
	}

	return OK;
}

Status DestroyArray(Array *A)
{
	if(A->base == NULL)
	{
		return ERROR;
	}

	free(A->base);
	A->base = NULL;
	
	if(A->bounds == NULL)
	{
		return ERROR;
	}

	free(A->bounds);
	A->bounds = NULL;
	
	if(A->constants == NULL)
	{
		return ERROR;
	}
	
	free(A->constants);
	A->constants = NULL;
	
	return OK;
}

Status Locate(Array A, va_list ap, int *off)
{
	int i;
	int ind;
	*off = 0;
	
	for(i = 0; i < A.dim; ++i)
	{
		ind = va_arg(ap,int);
	
		if(ind < 0 || ind >= A.bounds[i])
		{
			return OVERFLOW;
		}

		*off += A.constants[i] * ind;
	}

	return OK;
}

Status Value(Array A, ElemType *e, ...)
{
	int off;
	int result;
	va_list ap;
	va_start(ap,e);
	
	if((result = Locate(A,ap,&off)) <= 0)
	{
		return result;
	}
	
	*e = *(A.base + off);
	
	return OK;
}

Status Assign(Array *A, ElemType e,...)
{
	int off;
	int result;
	va_list ap;
	va_start(ap,e);
	
	if((result = Locate(*A,ap,&off)) <= 0)
	{
		return result;
	}
	
	*(A->base + off) = e;

	return OK;
}
