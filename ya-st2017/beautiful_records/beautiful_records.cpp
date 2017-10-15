/*
 *  Автор: Роман Кошелев  #8134076736
 *
 *  Compilation: clang++ beautiful_records.cpp -O2 -std=c++11 -Weverything -Wno-missing-prototypes -Wno-c++98-compat -Werror 
 *			       -Wno-sign-conversion -Wno-conversion
 *  
 *  
 *  Красивые записи
 *  
 */

#include <cstdlib>
#include <string>
#include <iostream>

std::string pre(std::string &str_prim)
{
	std::string  str_ult;
	str_ult.reserve(str_prim.size());
	bool flag1 = true, flag2 = true;
	for (unsigned char n : str_prim) {
		if (isalpha(n))
		{
			if (flag2) {
				str_ult.push_back(toupper(n));
			}
			else {
				str_ult.push_back(tolower(n));
			}
			flag1 = flag2 = false;
		}
		else if (n == ' ' && !flag1) {
			str_ult.push_back(' ');
			flag1 = true;
		} 
		else if (n == '.') {
			if (flag2) {
				return "-1";
			}
			if (flag1) {
				str_ult.pop_back();
			}
			str_ult.push_back('.');
			str_ult.push_back(' ');
			flag1 = flag2 = true;

		}
	}
	if (!flag2) {
		return "-1";
	}
	if (str_ult.size() > 0) {
		str_ult.pop_back();
	}
	else {
		return "-1";
	}
	
	return str_ult;
}

int main()
{
	std::string str_prim, str_ult;
	std::getline(std::cin, str_prim);
	str_ult = pre(str_prim);
	std::cout << str_ult << "\n";
	return EXIT_SUCCESS;
}
