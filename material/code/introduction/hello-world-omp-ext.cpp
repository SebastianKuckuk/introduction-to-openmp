#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    std::cout << "This is serial" << std::endl;

    #pragma omp parallel
        std::cout << "This is parallel" << std::endl;

    std::cout << "This is serial" << std::endl;
}
