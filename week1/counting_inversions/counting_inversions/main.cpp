#include <common.h>

uint32_t merge(size_t i, size_t j, size_t middle, std::vector<int32_t>& arr, std::vector<int32_t>& aux)
{
	uint32_t inversions(0);
	//print_array(arr, arr.size());
	
	for (size_t idx = i; idx <= j; ++idx)
		aux[idx] = arr[idx];
	
	size_t current(i), left(i), right(middle + 1);

	while (true)
	{
		if (aux[left] > aux[right])
		{
			arr[current++] = aux[right++];
			inversions = inversions + (middle - left) + 1;
		}
		else
		{
			arr[current++] = aux[left++];
		}
		
		if (left > middle || right > j)
			break;
	}
	
	if (left <= middle)
		for (int idx = left; idx <= middle; ++idx)
			arr[current++] = aux[idx];

	if (right <= j)
		for (int idx = right; idx < j; ++idx)
			arr[current++] = aux[idx];
			
	return inversions;
}

// Returns number of inversions
uint32_t merge_sort(size_t i, size_t j, std::vector<int32_t>& arr, std::vector<int32_t>& aux)
{
	uint32_t inversions(0);

	if (j <= i)
		return 0;

	size_t middle = (i + j) / 2;
	
	inversions = merge_sort(i, middle, arr, aux);
	inversions += merge_sort(middle + 1, j, arr, aux);
	//std::cout << i << " " << middle << " " << j << std::endl;
	inversions += merge(i, j, middle, arr, aux);
	//std::cout << inversions << std::endl;
	return inversions;
}

int main(int argc, char** argv)
{
	std::vector<int32_t> arr;
	//read_from_file(L"F:\\dev\\coursera\\ADAA_Part1\\week1\\artefacts\\IntegerArray_Lite.txt", arr);
	read_from_file(L"..\\..\\artefacts\\_bcb5c6658381416d19b01bfc1d3993b5_IntegerArray.txt", arr);
	//print_array(arr, arr.size());
	std::vector<int32_t> aux(arr.size());
	std::cout << "inversions: " << merge_sort(0, arr.size() - 1, arr, aux) << std::endl;
	//print_array(arr, arr.size());
	return 0;
}