#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "myset.h"
#include "stackSet.h"

int calculate(stack *st, char oper)
{
	set p2 = pop(st);
	set p1 = pop(st);
	set buf;
	if (oper == 'U') {
		buf = unionSet(p1, p2);
	}
	else if (oper == '\\') {
		buf = minusSet(p1, p2);
	}
	else  {
		buf = intersectionSet(p1, p2);
	}
	freeSet(p1);
	freeSet(p2);
	if (push(st, buf)) {
		return 1;
	}
	return 0;
}

int provCorect(const char * str)
{
	char iter = '(';
	int ch1 = 0, ch2 = 0;
	const size_t endLoop = strlen(str);
	for (size_t i = 0; i < endLoop; ++i)
	{
		switch (str[i])
		{
		case ' ': break;
		case '(': if (iter != '(' && iter != '[' && iter != '^') return 1; iter = str[i]; ch1++; break;
		case ')': if (iter != ')' && iter != ']') return 1; iter = str[i]; ch1--; break;
		case '[': if (iter != '(' && iter != '^') return 1; iter = str[i]; ch2++;  break;
		case ']': if (iter != '0' && iter != '[') return 1; iter = str[i]; ch2--;  break;
		case ',': if (iter != '0') return 1; iter = str[i]; break;

		case '^':
		case '\\':
		case 'U': if (iter != ')' && iter != ']') return 1; iter = '^'; break;

		default:
			if (iter != '0' && iter != '[' && iter != ',') return 1;
			iter = '0';
		}
	}

	if ((iter != ')' && iter != ']') || ch1 != 0 || ch2 != 0) return 1;
	return 0;
}

set kernel(const char *str)
{
	if (provCorect(str) != 0) {
		return setNULL;
	}
	stack* stackSet = intitStack();
	if (stackIsNull(stackSet)) {
		return setNULL;
	}
	char stackOper[0xff];
	size_t stPtrOper = 0;

	for (const char* i = str; *i != '\0'; ++i)
	{
		const char c = *i;
		switch (c)
		{
		case ' ':
			break;

		case 'U':
		case '\\':
		case ')':
			while (stPtrOper != 0)
			{
				const char op = stackOper[--stPtrOper];
				if (op == '(') {
					if (c != ')') stPtrOper++;
					break;
				}
				if (calculate(stackSet, op) != 0) {
					freeStack(stackSet);
					return setNULL;
				}
			}

			if (c != ')') stackOper[stPtrOper++] = c;
			break;

		case '^':
			while (stPtrOper != 0)
			{
				const char op = stackOper[stPtrOper - 1];
				if (op == '(' || op == 'U' || op == '\\') {
					break;
				}
				if (calculate(stackSet, op) != 0) {
					freeStack(stackSet);
					return setNULL;
				}
				stPtrOper--;
			}
			stackOper[stPtrOper++] = c;
			break;

		case '(':
			stackOper[stPtrOper++] = c;
			break;

		default:
			if (push(stackSet, strToSet(&i))) {
				freeStack(stackSet);
				return setNULL;
			}
			break;
		}
	}

	while (stPtrOper != 0) {
		const char op = stackOper[--stPtrOper];
		if (calculate(stackSet, op) != 0) {
			freeStack(stackSet);
			return setNULL;
		}
	}
	set buf = pop(stackSet);
	freeStack(stackSet);
	return buf;
}

#define MAX_LEN 0xff

int tests()
{
	const char* testMas[][2] = { { "[3,5,7,9,11,13,15]^([2,4,6,8,10,12,14] U [ 8,8,8 ,64]", "[error]" },
				     { "     [3,5,7,9,11,13,15]^[2,4,6,8,10,12,14] U [ 8 ,64]", "[8,64]" },
				     { "([1,     2  , 3 ] U [1,2,42,8] U[])^[1, 8, 3,13]", "[1,3,8]" },
				     { "([1,     2  , 3 ] U [1,2,42,8]^[])^[1, 8, 3,13]", "[1,3]" },
				     { "([1,2,3]\\[1,2,42,8])^[1, 8, 3,13]", "[3]" },
				     { "([]U[1]U[2]U[3])", "[1,2,3]" },
				     { "[1,2,3]\\[1,2,42,8,3]", "[]" },
				     { "[]U[1]U[2]U[3]", "[1,2,3]" },
				     { "[]U[1]U[2]^[2,3]", "[1,2]" },
				     { "[]", "[]" }
				   };
	char str[MAX_LEN];
	for (size_t i = 0; i < sizeof(testMas) / (sizeof(char*) * 2); ++i) {
		if (strcmp(setToStr(kernel(testMas[i][0]), str), testMas[i][1]) != 0) {
			return 1;
		}
	}
	return 0;
}

int main()
{
	assert(tests() == 0);
	char str[MAX_LEN];
	if (fgets(str, MAX_LEN, stdin) != NULL)
	{
		if (str[strlen(str) - 1] == '\n') {
			str[strlen(str) - 1] = '\0';
		}

		set res = kernel(str);
		printf("%s\n", setToStr(res, str));
		freeSet(res);
	}
	return EXIT_SUCCESS;
}
