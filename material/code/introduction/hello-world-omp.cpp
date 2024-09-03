#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
    #pragma omp parallel
    {
        std::cout << "Hello world" << std::endl;
    }
}
