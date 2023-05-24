#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <execution>

int divCount(int num);

int main()
{
    std::setlocale(LC_ALL, "Russian");
    //rand(time(0)) //#include <ctime>

    //1 //5e5 //1e6 // 2e6
    //2 //5e8 //1e9 //2e9
    
    //1
    
   /* const long long vsize = 5e5;
    std::vector<int> v1, v2;
    v1.resize(vsize);
    v2.resize(vsize);

    for (size_t i = 0; i < vsize; i++)
       v1[i] = rand() + 100001;
    for (size_t i = 0; i < vsize; i++)
        v2[i] = 0;

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    std::transform(std::execution::seq, v1.begin(), v1.end(), v2.begin(), divCount);

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << diff.count() << "s\n";
     */


     //2 test
     
     //std::vector<int> v1Test = { 1, 5, 6, 16, 32 };
     //int s = std::reduce(std::execution::seq, v1Test.begin(), v1Test.end());
     //for (size_t i = 0; i < 5; i++)
     //    std::cout << v1Test[i] + " ";
     //std::cout << std::endl << s << std::endl;
     //
     //2
     
     //const long long vsize = 2e9;
     //std::vector<int> v1;
     //v1.resize(vsize);

     //for (size_t i = 0; i < vsize; i++)
     //    v1[i] = rand() % 5 + 1;

     //std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
     //start = std::chrono::high_resolution_clock::now();

     //long long sum = std::reduce(std::execution::par_unseq, v1.begin(), v1.end());

     //end = std::chrono::high_resolution_clock::now();
     //std::chrono::duration<double> diff = end - start;
     //std::cout << diff.count() << "s\n";
     //std::cout << sum << std::endl;
     

     //3 test
     /*
     std::vector<std::vector<int>> m1Test(2, std::vector<int>(2));
     m1Test[0] = { 2, 4 };
     m1Test[1] = { 4, 2 };
     std::vector<std::vector<int>> m2Test(2, std::vector<int>(2));
     m2Test[0] = { 1, 3 };
     m2Test[1] = { 3, 1 };
     std::vector<std::vector<int>> m3Test(2, std::vector<int>(2));

     for (size_t i = 0; i < 2; i++)
     {
         for (size_t j = 0; j < 2; j++)
         {
             m3Test[i][j] = std::transform_reduce(
                 std::execution::seq,
                 m1Test[i].begin(), m1Test[i].end(),
                 m2Test[j].begin(), 0);
         }
     }

     for (size_t i = 0; i < 2; i++)
     {
         for (size_t j = 0; j < 2; j++)
         {
             std::cout << m3Test[i][j] + " ";
         }
         std::cout << std::endl;
     }
     */
     //3 считается что B уже транспонирована
     
     const int size = 2048;
     std::vector<std::vector<int>> A(size, std::vector<int>(size));
     std::vector<std::vector<int>> B(size, std::vector<int>(size));
     std::vector<std::vector<int>> C(size, std::vector<int>(size));

     for (size_t i = 0; i < size; i++)
         for (size_t j = 0; j < size; j++)
             A[i][j] = rand() % 5 + 1;
     for (size_t i = 0; i < size; i++)
         for (size_t j = 0; j < size; j++)
             B[i][j] = rand() % 5 + 1;

     std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
     start = std::chrono::high_resolution_clock::now();


     for (size_t i = 0; i < size; i++)
     {
         for (size_t j = 0; j < size; j++)
         {
             C[i][j] = std::transform_reduce(
                 std::execution::par_unseq,
                 A[i].begin(), A[i].end(),
                 B[j].begin(), 0);
         }
     }

     end = std::chrono::high_resolution_clock::now();
     std::chrono::duration<double> diff = end - start;
     std::cout << diff.count() << "s\n";
     

     //4 test
     
   /*  std::vector<int> v = { 5, 8, 1, 7 };
     for (size_t i = 0; i < v.size(); i++)
         std::cout << v[i] + " ";
     std::cout << std::endl;

     std::sort(std::execution::seq, v.begin(), v.end());

     for (size_t i = 0; i < v.size(); i++)
         std::cout << v[i] + " ";
     std::cout << std::endl;*/
     
     //4

    //const int vsize = 1e9;
    //std::vector<int> v;
    //v.resize(vsize);
    //for (size_t i = 0; i < vsize; i++)
    //    v[i] = rand() % 1000 + 1;

    //std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    //start = std::chrono::high_resolution_clock::now();

    //std::sort(std::execution::seq, v.begin(), v.end());

    //end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> diff = end - start;
    //std::cout << diff.count() << "s\n";
    //std::cout << v[0] << std::endl;

    system("pause");
    return 0;
}

int divCount(int num)
{
    int c = 0;
    int numSqrt = floor(sqrt(num));
    if (num == numSqrt * numSqrt) c++;
    for (int i = 1; i < numSqrt; i++)
        if (num % i == 0) c += 2;

    return c;
}
