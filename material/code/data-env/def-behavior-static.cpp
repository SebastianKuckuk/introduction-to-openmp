#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    static int staticVar = 30;

    #pragma omp parallel
        //# implicit shared(staticVar)
        //# bad practice -- race condition
        std::cout << ++staticVar << std::endl;

    std::cout << staticVar << std::endl;
}
