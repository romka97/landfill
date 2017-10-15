/*
 *  Автор: Роман Кошелев  #8134076736
 *  
 *  Compilation: clang++ Athletes.cpp -O2 -std=c++11 -Weverything -Wno-missing-prototypes -Wno-c++98-compat -Werror
 *  
 *  Атлеты
 *  
 *  В город N приехал цирк с командой атлетов.
 *  Они хотят удивить горожан города N — выстроить из своих тел башню максимальной высоты. 
 *  Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на плечах, третий стоит на плечах у второго и т.д.
 *  Каждый атлет характеризуется силой si (kg) и массой mi (kg).
 *  Сила — это максимальная масса, которую атлет способен держать у себя на плечах.
 *  К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической подготовкой, и у них не было времени на изучение языков программирования.
 *  Помогите им, напишите программу, которая определит максимальную высоту башни, которую они могут составить.
 *  Известно, что если атлет тяжелее, то он и сильнее: если mi>mj, то si > sj.
 *  Атлеты равной массы могут иметь различную силу.
 * 
 */

#include <iostream>
#include <algorithm>
#include <cstdlib>

size_t calculate(std::pair<int, int> *mas, std::size_t sizeMas)
{
	int sumMas = mas[0].second;
	size_t count = 1;
	for (size_t i = 1; i < sizeMas; ++i)
	{
		if (mas[i].first >= sumMas) {
			sumMas += mas[i].second;
			count++;
		}
	}
	return count;
}


int main() {
	auto *mas = new std::pair<int, int>[100000];
	std::size_t sizeMas = 0;

	int mi = 0, si = 0;
	while (std::cin >> mi >> si) {
		mas[sizeMas].first = si;
		mas[sizeMas].second = mi;
		sizeMas++;
	}

	std::sort(mas, mas + sizeMas);

	std::cout << calculate(mas, sizeMas);

	delete[] mas;

	return EXIT_SUCCESS;
}
