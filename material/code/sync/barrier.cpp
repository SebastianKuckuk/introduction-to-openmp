#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    //# can be stand-alone, but that might not be too useful
    #pragma omp barrier

    //# or in an enclosing region
    #pragma omp parallel num_threads(4)
    {
        std::cout << omp_get_thread_num() << std::endl;
        #pragma omp barrier
        std::cout << 10 * omp_get_thread_num() << std::endl;
    }
}
