#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <omp.h>

int main()
{
	int N = 3;
	int num_threads = 3;
	double start, end, diff;

	int** A = new int* [N];
	for (size_t i = 0; i < N; i++)
		A[i] = new int[N];

	int** B = new int* [N];
	for (size_t i = 0; i < N; i++)
		B[i] = new int[N];

	int** C = new int* [N];
	for (size_t i = 0; i < N; i++)
		C[i] = new int[N];

	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			A[i][j] = rand() % 100 + 1;

	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			B[i][j] = rand() % 100 + 1;

	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			C[i][j] = 0;


	start = omp_get_wtime();

#pragma omp parallel num_threads(num_threads)
	{
#pragma omp for schedule(static)
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < N; k++)
			{
				for (int j = 0; j < N; j++)
				{
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
	}

	end = omp_get_wtime();
	diff = end - start;
	std::cout << diff << std::endl;
	std::cout << std::endl;

	for (size_t i = 0; i < N; i++)
		delete[] A[i];
	delete[] A;

	for (size_t i = 0; i < N; i++)
		delete[] B[i];
	delete[] B;

	for (size_t i = 0; i < N; i++)
		delete[] C[i];
	delete[] C;

	system("pause");
	return 0;
}
