#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int someVar = 30;
    #pragma omp parallel default(none)
        std::cout << ++someVar << std::endl;

    std::cout << someVar << std::endl;
}
