/*
 *  Автор: Роман Кошелев  #8134076736
 *  
 *  Compilation: clang++ The_next_element.cpp -O2 -std=c++11 -Weverything -Wno-missing-prototypes -Wno-c++98-compat -Werror
 *  
 *  Следующий элемент
 *  
 *  Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 *  Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A,
 *  равного или превосходящего B[i]: A[k] >= B[i].
 *  Если такого элемента нет, выведите n.
 *  Время работы поиска k для каждого элемента B[i]: O(log(k)).
 *  n, m ? 10000.
 *  
 *  input:			output:
 *   2 1			 1
 *   1 2
 *   2
 *   
 *  input:			output:
 *   4 3			 1 3 0
 *   2 4 5 7
 *   4 6 1 
 *   
 */

#include <cstdlib>
#include <iostream>

std::size_t BinarySearch(int *mas, std::size_t left, std::size_t right, int num)
{
	while (left < right)
	{
		const std::size_t mid = (left + right) / 2;
		if (num <= mas[mid]) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return num <= mas[right] ? right : right;
}

std::size_t Search(int *mas, std::size_t count, int num)
{
	std::size_t i;
	for (i = 1; i*i < count; ++i) {
		if (mas[i*i] >= num) {
			return BinarySearch(mas, (i - 1)*(i - 1), i*i, num);
		}
	}
	return BinarySearch(mas, (i - 1)*(i - 1), count, num);
}

int main()
{
	std::size_t sizeA, sizeB;
	std::cin >> sizeA >> sizeB;
	int *masA = new int[sizeA];

	for (std::size_t i = 0; i < sizeA; ++i) {
		std::cin >> masA[i];
	}

	int masBi;
	for (std::size_t i = 0; i < sizeB; i++)
	{
		std::cin >> masBi;
		std::cout << Search(masA, sizeA, masBi) << " ";
	}

	delete[] masA;
	return EXIT_SUCCESS;
}
