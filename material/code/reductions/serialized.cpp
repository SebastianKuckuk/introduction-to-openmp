#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    int localSums[1024];
    #pragma omp parallel num_threads(1024)
        localSums[omp_get_thread_num()] = 1;

    for (auto i = 0; i < 1024; ++i)
        sum += localSums[i];

    std::cout << sum << std::endl;
}
