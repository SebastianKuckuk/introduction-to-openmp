#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int sharedVar = 20;
    #pragma omp parallel shared(sharedVar)
        std::cout << ++sharedVar << std::endl; //# race condition

    std::cout << sharedVar << std::endl;
}
