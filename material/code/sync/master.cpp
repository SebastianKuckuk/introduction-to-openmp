#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel num_threads(4)
    {
        //# this is deprecated
        #pragma omp master
            std::cout << omp_get_thread_num() << std::endl;

        //# this is the replacement ...
        #pragma omp masked
            std::cout << omp_get_thread_num() << std::endl;

        //# ... which allows using filter clauses
        #pragma omp masked filter(2)
        std::cout << omp_get_thread_num() << std::endl;
    }
}
