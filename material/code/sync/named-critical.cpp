#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel num_threads(4)
    {
        #pragma omp critical (A)
            std::cout << "A " << omp_get_thread_num() << std::endl;

        #pragma omp critical (B)
            std::cout << "B " << omp_get_thread_num() << std::endl;
    }
}
