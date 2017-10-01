/*  
 *  Автор: Роман Кошелев  #8134076736
 *
 *  Дано натуральное число N.
 *  Представить N в виде A + B, так, что НОД(A, B) максимален, A ? B.
 *  Вывести A и B.
 *  Если возможно несколько ответов - вывести ответ с минимальным A. n ? 10^7
 *  
 *  input:			output:
 *   35				 7 28
 *   
 */


#include <iostream>
#include <cstdlib>
#include <tuple>

std::pair<int, int> calc(int n)
{
	if (n % 2 == 0) {
		return { n / 2, n / 2 };
	}

	for (int i = 3; i*i <= n; i += 2) {
		if (n % i == 0) {
			return { n / i, n - (n / i) };
		}
	}
	return { 1, n - 1 };
}

int main()
{
	int n;
	std::cin >> n;
	int a, b;
	std::tie(a, b) = calc(n);
	std::cout << a << " " << b;
	return EXIT_SUCCESS;
}
