#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdint.h>

template <class T>
void print_array(T& array, int size) {
	for (int i = 0; i < size; i++)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

void read_from_file(const std::wstring& filepath, std::vector<int32_t>& arr)
{
	arr.clear();
	std::ifstream input(filepath);
	for (std::string line; std::getline(input, line);)
		arr.push_back(std::stoi(line));
}

#endif // _COMMON_H_