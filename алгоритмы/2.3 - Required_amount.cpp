/*
 *  Автор: Роман Кошелев  #8134076736
 * 
 *  Нужная сумма
 *  
 *  Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
 *  Найти количество таких пар индексов (i, j), что A[i] + B[j] = k.
 *  Время работы O(n + m). n, m ? 100000.
 *  Указание. Обходите массив B от конца к началу.
 *  
 *  input:				output:
 *   4                   3                 
 *	 -5 0 3 18
 *	 5
 *	 -10 -2 4 7 12
 *	 7
 *	 
 */

#include <iostream>
#include <cstdlib>

std::size_t countInd(std::size_t lenA, int *masA, std::size_t lenB, int *masB, int k)
{
	std::size_t	counter = 0;
	std::ptrdiff_t j = 0;

	for (std::ptrdiff_t i = lenB - 1; i >= 0; --i) 
	{
		for (; j < lenA; ++j) 
		{
			const int sum = masB[i] + masA[j];
			if (sum == k) {
				counter++;
			}
			else if (sum > k) {
				break;
			}
		}
	}
	return counter;
}

int main() {
	std::size_t sizeA = 0;
	std::cin >> sizeA;

	int *masA = new int[sizeA];
	for (std::size_t i = 0; i < sizeA; i++) {
		std::cin >> masA[i];
	}

	std::size_t sizeB = 0;
	std::cin >> sizeB;

	int *masB = new int[sizeB];
	for (std::size_t i = 0; i < sizeB; i++) {
		std::cin >> masB[i];
	}

	int k;
	std::cin >> k;

	const std::size_t result = countInd(sizeA, masA, sizeB, masB, k);
	std::cout << result;

	delete[] masA;
	delete[] masB;
	return EXIT_SUCCESS;
}
