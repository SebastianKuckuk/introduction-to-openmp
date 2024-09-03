#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    #pragma omp parallel reduction( + : sum )
    {
        #pragma omp for
        for (auto i = 0; i < 1024; ++i)
            sum += 1;

        #pragma omp for
        for (auto i = 0; i < 1024; ++i)
            sum += 2;
    }

    std::cout << sum << std::endl;
}
