#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            std::cout << omp_get_thread_num() << std::endl << std::endl;
        } //# implicit barrier

        std::cout << omp_get_thread_num() << std::endl;
    }
}
