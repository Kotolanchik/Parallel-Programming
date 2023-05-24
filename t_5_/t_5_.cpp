#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>

int main() {
	int N, M, K;
	double res;
	std::vector<long> v;

	std::cout << "Enter N: ";
	std::cin >> N;

	std::cout << "Enter M: ";
	std::cin >> M;

	K = N - M;

	v.reserve(N);
	for (int i = 0; i < N; i++)
	{
		v.push_back(i + 1);
	}

	long long nSum = 0;
	long localPowSum = 0;
	long powSum = 0;

	omp_set_nested(1);
#pragma omp parallel num_threads(2)
	{
#pragma omp sections
		{
#pragma omp section
			{
#pragma omp parallel num_threads(M) reduction(+: nSum)
				{
#pragma omp for schedule(static)
					for (int i = 0; i < N; ++i)
					{
						nSum += i + 1;
					}
				}
			}
#pragma omp section
			{
#pragma omp parallel num_threads(K) private(localPowSum)
				{
					localPowSum = 0;
#pragma omp for schedule(static)
					for (int i = 0; i < N; ++i)
					{
						localPowSum += v[i] * v[i];
					}
#pragma omp critical
					powSum += localPowSum;
#pragma omp flush(powSum)
					res = sqrt(powSum);
				}
			}
		}
	}

	std::cout << "NSum = " << nSum << std::endl;
	std::cout << "PowSum = " << powSum << std::endl;
	std::cout << "Res = " << res << std::endl;

	return 0;
}
