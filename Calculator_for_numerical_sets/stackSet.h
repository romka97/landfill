#pragma once
#include "myset.h"

typedef struct stack
{
	set *num;
	size_t len;
} stack;

int stackIsNull(stack *st);
int push(stack *st, set param);
set pop(stack *st);
stack* intitStack(void);
void freeStack(stack *st);
