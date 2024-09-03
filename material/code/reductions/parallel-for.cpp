#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    #pragma omp parallel for reduction( + : sum )
    for (auto i = 0; i < 1024; ++i)
        sum += 1;

    std::cout << sum << std::endl;
}
