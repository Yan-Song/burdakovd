#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "functions.c"

#ifndef KREVSTACK
#define KREVSTACK

struct node
{
	int typ; // 0: number[num], 1: function call[functionid], 2: operation[op],
                // 3: скобка[op], -1: EOF, -2: error
	char op;
	double num;
        struct func* function;
};

struct _stack{struct node v; struct _stack *next; };
#define stack struct _stack*

void push(stack *p, struct node data)
{	
	//printf("push(%d)\n", data);
	stack s;
	s=(stack)malloc(sizeof(struct _stack));
	s->v = data;
	s->next = *p;
	*p = s;
}

struct node pop(stack *p)
{
	assert((*p)!=NULL);
	stack tmp=*p;
	struct node v=tmp->v;
	*p = tmp->next;
	free(tmp);
	//printf("pop()=%d\n", v);
	return v;
}

struct node head(stack p)
// как pop() но не удаляет из стека
{
    assert(p!=NULL);
    return p->v;
}

int isEmpty(stack p)
{
	return (p==NULL);
}

stack emptyStack()
{
	return NULL;
}
#endif
