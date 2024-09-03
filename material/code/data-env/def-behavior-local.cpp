#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int someVar = 30;
    #pragma omp parallel
    {
        //# implicit private(localVar)
        int localVar = omp_get_thread_num();
        std::cout << ++localVar << std::endl;
    }

    std::cout << someVar << std::endl;
}
