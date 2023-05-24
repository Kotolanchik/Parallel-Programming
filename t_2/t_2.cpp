#include <iostream>
#include <omp.h>

void thread_process(int, int);

int main()
{
	int nthreads, tid, N;

	std::cout << "Enter N: ";
	std::cin >> N;

	omp_set_num_threads(2);

#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		printf("Hello World from thread = %d\n", tid);
		if (tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
		thread_process(tid, N);
	}

	return 0;
}

void thread_process(int tid, int N)
{
	if (tid == 0)
	{
		for (int i = 0; i < N; ++i)
		{
			printf("Num = %d from thread %d\n", i + 1, tid);
		}
	}
	else if (tid == 1)
	{
		for (int i = 0; i < N; ++i)
		{
			printf("Hello World from thread %d\n", tid);
		}
	}
}

