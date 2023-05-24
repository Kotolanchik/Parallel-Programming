#include <iostream>
#include <omp.h>

int main() {
	int N;
	int* arr1, * arr2, * result;

	std::cout << "Enter N: ";
	std::cin >> N;

	arr1 = new int[N];
	arr2 = new int[N];
	result = new int[N];

	for (int i = 0; i < N; i++)
	{
		arr1[i] = i;
		arr2[i] = i;
		result[i] = 0;
	}

	int index;

#pragma omp parallel shared(index)
	{
#pragma omp for schedule(static)
		for (index = 0; index < N; index++)
			result[index] = arr1[index] * arr2[index];
	}

	for (int i = 0; i < N; i++)
	{
		std::cout << arr1[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << arr2[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < N; i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;

	delete[] arr1;
	delete[] arr2;
	delete[] result;

	return 0;
}
