#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    constexpr auto N = 256 * 1024 * 1024;

    int *vec = new int[N];

    for (auto i = 0; i < N; ++i)
        vec[i] = i;

    auto start = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (auto i = 0; i < N; ++i)
        vec[i] *= 2;

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
