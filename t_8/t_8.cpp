#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <vector>

int main()
{
	int N = 2000;
	int num_threads = 8;
	double start, end, diff;

	int** A = new int* [N];
	for (size_t i = 0; i < N; i++)
		A[i] = new int[N];

	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			A[i][j] = rand() % 100 + 2;

	/*
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			std::cout << A[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	*/

	start = omp_get_wtime();

	std::vector<int> localMins;
	for (int i = 0; i < N; i++)
		localMins.push_back(0);

	int localMin = INT32_MAX;
	int max = -1;

#pragma omp parallel num_threads(num_threads)
	{
#pragma omp for schedule(static)
		for (int i = 0; i < N; i++)
		{
			localMin = INT32_MAX;
			for (int j = 0; j < N; j++)
			{
				if (A[i][j] < localMin)
					localMin = A[i][j];
			}
			localMins[i] = localMin;
		}
#pragma omp flush(localMins)
#pragma omp for schedule(static)
		for (int i = 0; i < N; ++i)
		{
#pragma omp critical
			if (localMins[i] > max)
				max = localMins[i];
		}
	}


	/*
	for (int min : localMins)
		std::cout << min << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	*/

	end = omp_get_wtime();
	diff = end - start;
	std::cout << diff << std::endl;
	std::cout << std::endl;

	std::cout << "max = " << max << std::endl;

	for (size_t i = 0; i < N; i++)
		delete[] A[i];
	delete[] A;

	system("pause");
	return 0;
}