#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel num_threads(4)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                std::cout << "section 0, thread " << omp_get_thread_num() << std::endl;
            }

            #pragma omp section
            {
                std::cout << "section 1, thread " << omp_get_thread_num() << std::endl;
            }
        } //# implicit barrier without nowait clause
    }
}
