#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    std::cout << omp_is_initial_device() << std::endl;

    #pragma omp target
    {
        printf("%d\n", omp_is_initial_device());
    }
}
