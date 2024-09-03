#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto sum = 0;

    #pragma omp target teams distribute parallel for reduction( + : sum )
    for (auto i = 0; i < 100; ++i)
        sum += i;

    std::cout << "Sum is " << sum << std::endl;
}
