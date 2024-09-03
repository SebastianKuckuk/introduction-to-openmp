#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int *vec = new int[10];
    for (auto i = 0; i < 10; ++i)
        vec[i] = i;

    #pragma omp target teams distribute parallel for
    //# due to the missing map clause, this example will not work
    for (auto i = 0; i < 10; ++i)
        vec[i] *= 2;

    for (auto i = 0; i < 10; ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    free(vec);
}
