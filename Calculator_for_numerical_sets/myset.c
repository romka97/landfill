#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "myset.h"

const set setNULL = { 0,0 };

static int strToInt(const char **str)
{
	int x = 0;
	while (isalnum((unsigned char)**str))
	{
		x *= 10;
		x += **str - '0';
		++(*str);
	}
	--(*str);
	return x;
}

static void insertionSort(int *num, size_t size)
{
	for (size_t i = 1; i < size; ++i) {
		for (size_t j = i; j > 0 && num[j - 1] > num[j]; --j) {
			const int buf = num[j - 1];
			num[j - 1] = num[j];
			num[j] = buf;
		}
	}
}

int setIsNull(set s)
{
	if (s.num == NULL) {
		return 1;
	}
	return 0;
}

char* setToStr(set p, char* str)
{
	if (setIsNull(p)) {
		strncpy(str, "[error]", 8);
	}
	else {
		strncpy(str, "[", 1);
		int strLen = 1;
		if (p.size != 0)
		{
			strLen += sprintf(str + strLen, "%d", p.num[0]);
			for (size_t i = 1; i < p.size; ++i) {
				strLen += sprintf(str + strLen, ",%d", p.num[i]);
			}
		}
		strncpy(str + strLen, "]", 2);
	}
	return str;
}

set initSet()
{
	set res;
	res.num = (int*)malloc(0xf * sizeof(int));
	res.size = 0;
	return res;
}

set initSetN(size_t count)
{
	set res;
	res.num = (int*)malloc(count * sizeof(int));
	res.size = 0;
	return res;
}

set strToSet(const char **str)
{
	set res = initSet();
	for (++(*str); **str != ']'; ++(*str))
	{
		const char c = **str;
		if (c == ' ' || c == ',') {
			continue;
		}
		res.num[res.size++] = strToInt(str);
	}
	insertionSort(res.num, res.size);
	return res;
}

void freeSet(set p)
{
	free(p.num);
}

set intersectionSet(set Lhs, set Rhs)
{
	set res = initSetN(Lhs.size);
	if (setIsNull(res)) {
		return res;
	}
	if (Lhs.size == 0 || Rhs.size == 0) {
		return res;
	}
	size_t RhsIter = 0;
	for (size_t i = 0; i < Lhs.size; ++i)
	{
		while (Lhs.num[i] > Rhs.num[RhsIter]) {
			RhsIter++;
			if (RhsIter == Rhs.size) {
				return res;
			}
		}
		if (Lhs.num[i] == Rhs.num[RhsIter]) {
			res.num[res.size++] = Lhs.num[i];
		}
	}
	return res;
}

set unionSet(set Lhs, set Rhs)
{
	set res = initSetN(Lhs.size + Rhs.size);
	if (setIsNull(res)) {
		return res;
	}
	size_t i = 0, j = 0;
	while (i < Lhs.size && j < Rhs.size)
	{
		if (Lhs.num[i] < Rhs.num[j]) {
			res.num[res.size++] = Lhs.num[i];
			++i;
		}
		else {
			if (Rhs.num[j] == Lhs.num[i]) ++i;
			res.num[res.size++] = Rhs.num[j];
			++j;
		}

	}
	if (i == Lhs.size) {
		memcpy(res.num + res.size, Rhs.num + j, (Rhs.size - j) * sizeof(int));
		res.size += (Rhs.size - j);
	}
	else {
		memcpy(res.num + res.size, Lhs.num + i, (Lhs.size - i) * sizeof(int));
		res.size += (Lhs.size - i);
	}
	return res;
}

set minusSet(set Lhs, set Rhs)
{
	set res = initSetN(Lhs.size);
	if (setIsNull(res)) {
		return res;
	}
	size_t i = 0, j = 0;
	while (i < Lhs.size && j < Rhs.size)
	{
		if (Lhs.num[i] < Rhs.num[j])
		{
			res.num[res.size++] = Lhs.num[i];
			++i;
		}
		else if (Lhs.num[i] > Rhs.num[j]) {
			++j;
		}
		else {
			++i; ++j;
		}
	}
	if (i != Lhs.size)
	{
		memcpy(res.num + res.size, Lhs.num + i, (Lhs.size - i) * sizeof(int));
		res.size += (Lhs.size - i);
	}
	return res;
}
