#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int *vec = new int[10];
    for (auto i = 0; i < 10; ++i)
        vec[i] = i;

    #pragma omp target enter data map(to: vec[0:10])

    #pragma omp target teams distribute parallel for
    for (auto i = 0; i < 10; ++i)
        vec[i] *= 2;

    #pragma omp target exit data map(from: vec[0:10])

    for (auto i = 0; i < 10; ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    free(vec);
}
