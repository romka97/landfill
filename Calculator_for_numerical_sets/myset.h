#pragma once

typedef struct set
{
	int *num;
	size_t size;
} set;

extern const set setNULL;

int setIsNull(set s);
char* setToStr(set p, char* str);
set strToSet(const char **str);
void freeSet(set p);
set intersectionSet(set Lhs, set Rhs);
set unionSet(set Lhs, set Rhs);
set minusSet(set Lhs, set Rhs);
