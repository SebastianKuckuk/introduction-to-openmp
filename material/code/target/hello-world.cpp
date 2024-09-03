#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    std::cout << "Hello from the CPU" << std::endl;

    #pragma omp target
    {
        printf("Hello from the GPU\n");
    } //# implicit synchronization with the target
}
