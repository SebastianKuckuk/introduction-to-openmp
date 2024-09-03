#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp requires unified_shared_memory

    int *vec = new int[10];
    for (auto i = 0; i < 10; ++i)
        vec[i] = i;

    #pragma omp target teams distribute parallel for // no map clauses
    for (auto i = 0; i < 10; ++i)
        vec[i] *= 2;

    for (auto i = 0; i < 10; ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    free(vec);
}
