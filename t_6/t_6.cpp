
#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

bool isPrime(int n);
int lpd(int);

int main()
{
	srand(time(0));
	int N = 1e7;
	int num_threads = 8;
	double start, end, diff;
	std::vector<long> v;

	v.reserve(N);
	for (int i = 0; i < N; ++i)
	{
		v.push_back(rand() % 900000 + 100001);
		//std::cout << v[i] << " ";
	}
	//std::cout << std::endl;

	start = omp_get_wtime();

#pragma omp parallel num_threads(num_threads)
	{
#pragma omp for schedule(static)
		for (int i = 0; i < N; i++)
			v[i] = lpd(v[i]);
	}

	end = omp_get_wtime();
	diff = end - start;
	std::cout << diff << std::endl;

	/*
	for (long i : v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	*/
	return 0;
}

int lpd(int n)
{
	int d = 1;
	while (!isPrime(n / d))
	{
		do
		{
			d++;
		} while (n % d != 0);
	}
	return n / d;
}

bool isPrime(int n)
{
	if (n == 1) return false;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0) return false;
	}
	return true;
}
