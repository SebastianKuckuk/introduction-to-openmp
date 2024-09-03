#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    constexpr auto N = 1024;
    int vec[N];

    #pragma omp parallel
    {
    #pragma omp for nowait
        for (auto i = 0; i < N / 2; ++i)
            vec[i] = i;

        //# no implicit barrier

    #pragma omp for nowait
        for (auto i = N / 2; i < N; ++i)
            vec[i] = i;
    }

    std::cout << vec[N - 1] << std::endl;
}
