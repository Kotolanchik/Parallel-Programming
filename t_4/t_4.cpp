#include <iostream>
#include <omp.h>
#include <vector>

int main()
{
	int N;
	std::vector<long> v;

	std::cout << "Enter N: ";
	std::cin >> N;

	v.reserve(N);
	for (int i = 0; i < N; i++)
	{
		v.push_back(pow(i, i));
		std::cout << v[i] << " ";
	}

	std::cout << std::endl;

	long max = 0;
	long local_max = 0;

#pragma omp parallel
	{
#pragma omp for schedule(static)
		for (int i = 0; i < N; ++i)
		{
			if (local_max < v[i])
			{
				local_max = v[i];
			}
		}
#pragma omp critical
		if (max < local_max)
		{
			max = local_max;
		}
	}

	std::cout << "Max = " << max << std::endl;

	return 0;
}
