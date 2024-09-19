#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #ifdef _OPENMP
        int tid = omp_get_thread_num();
        std::cout << tid << ": " << _OPENMP << std::endl;
    #else
        int tid = 0;
        std::cout << tid << ": " << "OpenMP disabled" << std::endl;
    #endif
}
