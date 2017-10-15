/*
 *  Автор: Роман Кошелев  #8134076736
 *
 *  Compilation: clang++ blocking.cpp -O2 -std=c++11 -Weverything -Wno-missing-prototypes -Wno-c++98-compat
 *  
 *  
 *  Блокировки
 *  
 */

#include <set>
#include <iostream>

struct Resource
{
	Resource(int _l, int _r, int _d) : l(_l), r(_r), d(_d) {}
	int l;
	int r;
	int d;
};

inline bool operator<(const Resource& lhs, const Resource& rhs)
{
	return lhs.l < rhs.l;
}

bool test_sub(std::set<Resource> &res, const int s, const Resource& ddd)
{
	auto i = res.lower_bound(ddd);
	
	while (i != res.end())
	{
		if (i->d > s) {
			if (ddd.r >= i->l) {
				return false;
			}
			break;
		}
		i = res.erase(i);
	}
	auto x = i;
	if (i != res.begin()) {
		--i;
		if (i->d > s) {
			if (ddd.l <= i->r) {
				return false; 
			}
		}
	}

	if (ddd.d > 1) {
		res.insert(x, ddd);
	}

	return true;
}


int main()
{
	int n, m;
	int s, l, r, d;
	std::cin >> n >> m;
	std::set<Resource> block;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> s >> l >> r >> d;
		if (test_sub(block, s, { l, r, d + s })) {
			std::cout << "Yes\n";  
		}
		else {
			std::cout << "No\n";
		}
	}
	return 0;
}
