#include <stdlib.h>
#include "stackSet.h"
#include "myset.h"

int stackIsNull(stack *st)
{
	if (st == NULL || st->num == NULL) {
		return 1;
	}
	return 0;
}

stack* intitStack(void)
{
	stack *st = malloc(sizeof(struct stack));
	if (st == NULL) {
		return NULL;
	}
	st->num = malloc(0xff * sizeof(set));
	st->len = 0;
	return st;
}

void freeStack(stack *st)
{
	for (size_t i = 0; i < st->len; ++i) {
		freeSet(st->num[i]);
	}
	free(st->num);
}

int push(stack *st, set param)
{
	if (setIsNull(param)) {
		return 1;
	}
	if (st->len == 0xff) {
		return 0;
	}
	st->num[st->len++] = param;
	return 0;
}

set pop(stack *st)
{
	if (st->len == 0) {
		return setNULL;
	}
	return st->num[--st->len];
}
