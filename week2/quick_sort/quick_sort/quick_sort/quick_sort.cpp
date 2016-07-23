#include <iostream>
#include <vector>
#include "../../../../common/common.h"

using namespace std;

enum PivotStrategy
{
	First,
	Middle,
	Last
};

int partition_first(std::vector<int>& array, int l, int r)
{
	int i = l + 1, pivot = array[l];
	for (int j = i; j <= r; j++)
	{
		if (array[j] < pivot)
		{
			std::swap(array[i], array[j]);
			i++;
		}
	}

	std::swap(array[l], array[i - 1]);
	return i - 1;
}

inline int find_median_of_three(std::vector<int>& array)
{
	int first_pos = 0;
	int length = array.size();
	int middle_pos = length % 2 ? length / 2 : (length / 2 - 1);
	int last_pos = length - 1;

	int first = array[first_pos];
	int middle = array[middle_pos];
	int last = array[last_pos];

	if (first <= middle) 
	{
		if (middle <= last)
			return middle_pos;
		else if (first <= last)
			return last_pos;
		return first_pos;
	}

	if (first <= last)
		return first_pos;

	else if (middle <= last)
		return last_pos;

	return middle_pos;
}

uint32_t quick_sort(std::vector<int>& array, int l, int r, PivotStrategy pivotStrategy)
{
	if (l < r)
	{
		uint32_t numberOfComparsions(r - l);
		int pivotPos(0);
		if (pivotStrategy == Middle)
		{
			int pivot = find_median_of_three(array);
			std::swap(array[0], array[pivot]);
		}
		else if (pivotStrategy == Last)
		{
			std::swap(array[l], array[r]);
		}

		pivotPos = partition_first(array, l, r);
		
		numberOfComparsions += quick_sort(array, l, pivotPos - 1, pivotStrategy);
		numberOfComparsions += quick_sort(array, pivotPos + 1, r, pivotStrategy);
		
		return numberOfComparsions;
	}
	else
	{
		return 0;
	}
}

int main()
{
	std::vector<int32_t> array;

	uint32_t numberOfComparsions(0);
	read_from_file(L"..//..//..//artefacts//_32387ba40b36359a38625cbb397eee65_QuickSort.txt", array);
	numberOfComparsions = quick_sort(array, 0, array.size() - 1, First);
	cout << "numberOfComparsions = " << numberOfComparsions;

	read_from_file(L"..//..//..//artefacts//_32387ba40b36359a38625cbb397eee65_QuickSort.txt", array);
	numberOfComparsions = quick_sort(array, 0, array.size() - 1, Last);
	cout << "numberOfComparsions = " << numberOfComparsions;

	read_from_file(L"..//..//..//artefacts//_32387ba40b36359a38625cbb397eee65_QuickSort.txt", array);
	numberOfComparsions = quick_sort(array, 0, array.size() - 1, Middle);
	cout << "numberOfComparsions = " << numberOfComparsions;

	return 0;
}