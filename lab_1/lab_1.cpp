#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>


int main()
{
    const int N = 512;

    //double pointers
    /*
    int** A = new int*[N];
    for (size_t i = 0; i < N; i++)
        A[i] = new int [N];


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
    */

    //single pointers

    int* AA = new int[N * N];
    int* BB = new int[N * N];
    int* CC = new int[N * N];

    for (size_t i = 0; i < N * N; i++)
        AA[i] = rand() % 100 + 1;
    for (size_t i = 0; i < N * N; i++)
        BB[i] = rand() % 100 + 1;
    for (size_t i = 0; i < N * N; i++)
        CC[i] = 0;



    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    start = std::chrono::high_resolution_clock::now();

    //double pointers
    /*
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    */

    //single pointers

    for (int k = 0; k < N; k++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                CC[N * i + j] += AA[N * i + k] * BB[N * k + j];
            }
        }
    }


    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << diff.count() << "s\n";

    //double pointers
    /*
    for (size_t i = 0; i < N; i++)
        delete[] A[i];
    delete[] A;

    for (size_t i = 0; i < N; i++)
        delete[] B[i];
    delete[] B;

    for (size_t i = 0; i < N; i++)
        delete[] C[i];
    delete[] C;
    */

    //single pointers

    delete[] AA;
    delete[] BB;
    delete[] CC;


    system("pause");
    return 0;
}

