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

        #pragma omp barrier

        //# this is the replacement ...
        #pragma omp masked
            std::cout << omp_get_thread_num() << std::endl;

        #pragma omp barrier

        int t = 2;
        //# ... which allows using filter clauses
        #pragma omp masked filter(t)
            std::cout << omp_get_thread_num() << std::endl;
    }
}
