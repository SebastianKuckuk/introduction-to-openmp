#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int privateVar = 10;
    #pragma omp parallel firstprivate(privateVar)
        std::cout << ++privateVar << std::endl;

    std::cout << privateVar << std::endl;
}
