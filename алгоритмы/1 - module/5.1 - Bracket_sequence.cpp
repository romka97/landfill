/*
 *  Автор: Роман Кошелев  #8134076736
 *  
 *  Compilation: clang++ Bracket_sequence.cpp -O2 -std=c++11 -Weverything -Wno-missing-prototypes -Wno-c++98-compat -Werror
 *  
 *  Скобочная последовательность
 *  
 *  Дан фрагмент последовательности скобок, состоящей из символов (){}[].
 *  Требуется определить, возможно ли продолжить фрагмент в обе стороны,
 *  получив корректную последовательность.
 *  Длина исходной последовательности ? 800000.
 *
 *  Формат ввода
 *  Строка, содержащая символы (){}[] и, возможно, перевод строки.
 *
 *  Формат вывода
 *  Если возможно - вывести минимальную корректную последовательность, иначе - напечатать "IMPOSSIBLE".
 *  
 */

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>

template<class T>
class stack
{
public:
	stack() : ptr_(nullptr), size_(0), maxsize_(0) {}
	void reserve(std::size_t count)
	{
		if (capacity() < count)
		{
			T* buf = new T[count];
			std::memcpy(buf, ptr_, size_ * sizeof(T));
			maxsize_ = count;

			delete[] ptr_;
			ptr_ = buf;
		}
	}

	void push(T val) {
		if (size_ == maxsize_) {
			reserve(size_ * 2 + 1);
		}
		ptr_[size_] = val;
		size_++;
	}
	std::size_t capacity() const { return maxsize_; }
	std::size_t size() const { return size_; }
	bool empty() const { return size_ == 0; }
	void pop() { --size_; }
	T top() { return ptr_[size_ - 1]; }
	~stack() { delete[] ptr_; }
private:
	T* ptr_;
	std::size_t size_;
	std::size_t maxsize_;
};

char transform(char p)
{
	switch (p)
	{
	case ')':
		return '(';
	case ']':
		return '[';
	case '}':
		return '{';
	case '(':
		return ')';
	case '[':
		return ']';
	case '{':
		return '}';
	default:
		return '\0';
	}
}

bool test(char *str)
{
	std::size_t lenStr = strlen(str);
	stack<char> right, left;
	for (std::size_t i = 0; i < lenStr; ++i)
	{
		const char c = str[i];
		if (c== '(' || c == '[' || c == '{') {
			right.push(c);
		} 
		else
		{
			if (right.empty()) {
				left.push(c);
			}
			else {
				const char temp = right.top();
				right.pop();
				if ((c == ')' && temp != '(') ||
				    (c == ']' && temp != '[') ||
				    (c == '}' && temp != '{'))
				{
					return false;
				}

			}
		}
	}

	std::memmove(str + left.size(), str, lenStr);
	lenStr += left.size();
	const std::size_t tempSize = left.size();
	for (std::size_t i = 0; i < tempSize; ++i) {
		str[i] = transform(left.top());
		left.pop();
	}
	while (!right.empty()) {
		str[lenStr++] = transform(right.top());
		right.pop();
	}
	str[lenStr] = '\0';
	return true;
}

int main()
{
	char *str = new char[800000 + 1];
	std::cin >> str;
	if (test(str)) {
		std::cout << str;
	}
	else {
		std::cout << "IMPOSSIBLE";
	}
	delete[] str;
	return EXIT_SUCCESS;
}
