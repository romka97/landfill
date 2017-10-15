/*
 *  Автор: Роман Кошелев  #8134076736
 *  
 *  Compilation: clang++ Queue_with_chunked_list.cpp -O2 -std=c++11 -Weverything -Wno-missing-prototypes -Wno-c++98-compat -Werror
 *  
 *  Очередь с динамическим буфером
 *  
 *  Реализовать очередь с динамическим зацикленным буфером.
 *  Обрабатывать команды push back и pop front.
 *  
 *  Формат входных данных.
 *  В первой строке количество команд n. n ? 1000000.
 *  Каждая команда задаётся как 2 целых числа: a b.
 *  a = 2 - pop front
 *  a = 3 - push back
 *  Если дана команда pop front, то число b - ожидаемое значение.
 *  Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
 *
 *  Формат вывода
 *  Требуется напечатать YES - если все ожидаемые значения совпали.
 *  Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 *  
 */

#include <iostream>
#include <cstdlib>
#include <cassert>

template<class T, std::size_t N>
struct number
{
	number(T num_, number<T, N> *ptr) : next(ptr) { num[0] = num_; }
	T num[N];
	number<T, N> *next;
};

template<class T, std::size_t N>
struct circular_buffer
{
	using Myt = number<T, N>;
	circular_buffer() : ptr_push(nullptr), first(0), last(0) {}
	
	void push_back(T val) {
		if (ptr_push != nullptr) {
			if (last != N) {
				ptr_push->num[last] = val;
				last++;
			}
			else {
				ptr_push->next = new Myt(val, ptr_push->next);
				ptr_push = ptr_push->next;
				last = 1;
			}
		}
		else {
			ptr_push = new Myt(val, nullptr);
			ptr_push->next = ptr_push;
			last = 1; 
		}
	}

	T pop_front() {
		if (ptr_push == nullptr) {
			return -1;
		}
		if (ptr_push->next == ptr_push) {
			T res = ptr_push->num[first++];
			if (first == N || first == last)
			{
				delete ptr_push;
				ptr_push = nullptr;
				first = 0;
			}
			return res;
		}
		T res = ptr_push->next->num[first++];
		if (first == N) {
			Myt *buf = ptr_push->next;
			ptr_push->next = ptr_push->next->next;
			delete buf;
			first = 0;
		}
		return res;
	}

	~circular_buffer()
	{
		if (ptr_push != nullptr) {
			while (ptr_push->next != ptr_push) {
				Myt *buf = ptr_push->next;
				ptr_push->next = ptr_push->next->next;
				delete buf;
			}
			delete ptr_push;
		}
	}
private:
	Myt *ptr_push;
	int first;
	int last;
};


int main()
{
	std::size_t n;
	std::cin >> n;
	circular_buffer<int, 16> buf;
	int a, b;
	bool flag = true;
	for (std::size_t i = 0; i < n; ++i)
	{
		std::cin >> a >> b;
		assert(a == 2 || a == 3);
		if (a == 3) {
			buf.push_back(b);
		}
		else {
			if (buf.pop_front() != b) {
				flag = false;
				break;
			}
		}
	}
	if (flag) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	return EXIT_SUCCESS;
}
