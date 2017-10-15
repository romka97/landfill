/*
 *  Автор: Роман Кошелев  #8134076736
 *
 *  Compilation: clang++ game.cpp -O2 -std=c++14 -Weverything -Wno-missing-prototypes -Wno-c++98-compat -Werror -Wno-sign-conversion
 *  
 *  
 *  Игра
 *  
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <cassert>
#include <cstring>

class Matrix
{
public:
	Matrix(std::size_t height, std::size_t width) noexcept : size_x(width), size_y(height)
	{
		ptr = std::make_unique<int[]>((height + 2)*(width + 2));
		std::memset(ptr.get(), 0, (height + 2)*(width + 2) * sizeof(int));
	}

	Matrix(Matrix &&obj) noexcept
	{
		ptr = std::move(obj.ptr);
		size_x = obj.size_x;
		size_y = obj.size_y;
	}

	Matrix& operator=(Matrix &&obj) && = delete;
	Matrix& operator=(Matrix &&obj) & noexcept
	{
		ptr = std::move(obj.ptr);
		size_x = obj.size_x;
		size_y = obj.size_y;
		return *this;
	}

	std::size_t getSizeX() const
	{
		return size_x;
	}

	std::size_t getSizeY() const
	{
		return size_y;
	}

	int* operator[] (std::ptrdiff_t superscript)
	{
		assert(superscript < (static_cast<std::ptrdiff_t>(getSizeY()) + 1));
		return ptr.get() + (size_x + 2)*(superscript + 1) + 1;
	}
private:
	std::unique_ptr<int[]> ptr;
	std::size_t size_x, size_y;
};

std::istream& operator>>(std::istream &input, Matrix &obj)
{
	for (std::size_t i = 0; i < obj.getSizeY(); ++i) {
		for (std::size_t j = 0; j < obj.getSizeX(); ++j) {
			input >> obj[i][j];
		}
	}
	return input;
}

std::ostream& operator<< (std::ostream & output, Matrix &obj)
{
	for (std::size_t i = 0; i < obj.getSizeY(); ++i) {
		for (std::size_t j = 0; j < obj.getSizeX(); ++j) {
			output << obj[i][j] << " ";
		}
		output << std::endl;
	}
	return output; 
}

void transformation(Matrix &obj)
{
	for (std::size_t i = 0; i < obj.getSizeY(); ++i) {
		for (std::size_t j = 0; j < obj.getSizeX(); ++j) {
			--obj[i][j];
			obj[i][j] = ((obj[i][j] & 1) << 3) + ((obj[i][j] & 2) >> 1);
		}
	}
}

Matrix play(Matrix &initial, int k)
{
	Matrix received(initial.getSizeY(), initial.getSizeX());
	Matrix counter(initial.getSizeY(), initial.getSizeX());
	bool flag = true;
	while (k-- > 0 && flag) {
		flag = false;
		for (std::size_t i = 0; i < initial.getSizeY(); ++i) {
			for (std::size_t j = 0; j < initial.getSizeX(); ++j) {
				received[i][j] = initial[i][j + 1]
							   + initial[i][j - 1]
							   + initial[i + 1][j]
							   + initial[i - 1][j];
				if (received[i][j] >= (1 << 4)) {
					received[i][j] = (1 << 3);
				}
				else if (received[i][j] > 0) {
					received[i][j] = 1;
				}
				else {
					received[i][j] = 0;
				}
				if (received[i][j] != initial[i][j]) {
					++counter[i][j];
					flag = true;
				}
			}
		}
		std::swap(received, initial);
	}
	return counter;
}

int main() 
{
	int n, m, k;
	std::cin >> n >> m >> k;
	Matrix initial(n, m);
	std::cin >> initial;
	transformation(initial);
	Matrix b = play(initial, k);
	std::cout << b;
	return EXIT_SUCCESS;
}
