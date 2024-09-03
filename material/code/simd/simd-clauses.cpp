#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    constexpr auto N = 1024;
    int *vec;
    vec = (int*)aligned_alloc(64, 1024 * sizeof(int));

    #pragma omp simd simdlen(128) aligned(vec:64)
    for (auto i = 0; i < N; ++i)
        vec[i] = i;

    std::cout << vec[N - 1] << std::endl;

    free(vec);
}
