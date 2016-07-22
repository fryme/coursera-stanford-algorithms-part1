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

int partition(std::vector<int>& array, int l, int r, int pivot)
{
	//cout << "l " << l << " r " << r << endl;
	
	int i = l + 1;

	for (int j = i; j <= r; ++j)
	{
		if (array[j] < pivot)
		{
			//cout << "swap: " << array[i] << " and " << array[j] << endl;
			std::swap(array[i], array[j]);
			//print_array(array, array.size());
			i += 1;
		}
	}

	std::swap(array[l], array[i-1]);
	//print_array(array, array.size());
	//cout << "i " << --i << endl;
	--i;
	return i;
}

int partition_right(std::vector<int>& array, int l, int r)
{
	int pivot = array[r];
	int i = 
	for (int )
}

void quick_sort(std::vector<int>& array, int l, int r, 
				int& numberOfComparsions, PivotStrategy pivotStrategy)
{
	if (l < r)
	{
		int p(0);
		if (pivotStrategy == First)
			p = partition(array, l, r, array[l]);
		else if (pivotStrategy == Middle)
			p = partition(array, l, r, array[l]);
		else
			p = partition(array, l, r, array[r]);

		//cout << "p: " << p << " l: " << l << " r: " << r << endl;
		
		numberOfComparsions += (p - 1 - l - 1);
		quick_sort(array, l, p - 1, numberOfComparsions, pivotStrategy);
		numberOfComparsions += (r - p + 1 - 1);
		quick_sort(array, p + 1, r, numberOfComparsions, pivotStrategy);
	}
}

int main()
{
	std::vector<int32_t> array;
	
	array.push_back(3);
	array.push_back(4);
	array.push_back(2);
	array.push_back(6);
	array.push_back(9);
	array.push_back(1);
	
	//print_array(array, array.size());
	int numberOfComparsions(0);
	read_from_file(L"..//..//..//artefacts//_32387ba40b36359a38625cbb397eee65_QuickSort.txt", array);

	quick_sort(array, 0, array.size() - 1, numberOfComparsions);
	//print_array(array, array.size());
	cout << "numberOfComparsions = " << numberOfComparsions;
	return 0;
}