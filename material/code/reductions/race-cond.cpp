#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    #pragma omp parallel num_threads(1024)
        //# race condition
        sum += 1;

    std::cout << sum << std::endl;
}
