#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    constexpr auto N = 1024;
    int vec[N];

    #pragma omp simd
    for (auto i = 0; i < N; ++i)
        vec[i] = i;

    std::cout << vec[N - 1] << std::endl;

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
