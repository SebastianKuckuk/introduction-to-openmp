#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int vec[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    #pragma omp target teams distribute parallel for
    for (auto i = 0; i < 10; ++i)
        vec[i] *= 2;

    for (const auto& val : vec)
        std::cout << val << " ";
    std::cout << std::endl;
}
