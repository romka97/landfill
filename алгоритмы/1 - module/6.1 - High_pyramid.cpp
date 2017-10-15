/*
 *  Автор: Роман Кошелев  #8134076736
 *  
 *  Compilation: clang++ High_pyramid.cpp -O2 -std=c++11 -Weverything -Wno-missing-prototypes -Wno-c++98-compat -Werror
 *  
 *  Дано N кубиков. 
 *  Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
 *  Каждый вышележащий слой пирамиды должен быть не больше нижележащего. N ≤ 200.
 *
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstdint>

uint64_t calculate(std::size_t numberCube)
{
	uint64_t **table = new uint64_t *[numberCube];
	uint64_t *memory = new uint64_t[(numberCube + 1)*numberCube / 2];
	
	std::size_t memoryIter = 0;
	for (std::size_t i = 0; i < numberCube; ++i) {
		table[i] = memory + memoryIter;
		memoryIter += numberCube - i;
	}

	for (std::size_t count = 0; count < numberCube; ++count)
	{
		for (std::size_t n = 0; n < count + 1; ++n)
		{
			const std::size_t m = count - n;   
			if (m == 0) {
				table[m][n] = 1;
			}
			else {
				table[m][n] = 0;
				for (std::size_t j = 0; j < m && j <= n; ++j) { 
					table[m][n] += table[m - j - 1][j];
				}
			}
		
		}
	}
	uint64_t ch = 0;
	for (std::size_t i = 0; i < numberCube; ++i) {
		ch += table[i][numberCube - i - 1];
	}
	delete[] memory;
	delete[] table;
	return ch;
}

int main() {
	std::size_t blocks;
	std::cin >> blocks;

	std::cout << calculate(blocks) << '\n';

	return EXIT_SUCCESS;
}
