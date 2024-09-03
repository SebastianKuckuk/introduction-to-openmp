#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    int a = 1, b = 2, c = 3;
    bool deferred = false;

    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task if(deferred)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * a));
            std::cout << "thread " << omp_get_thread_num() << ": a = " << a << std::endl;
        }

        #pragma omp task if(deferred)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * b));
            std::cout << "thread " << omp_get_thread_num() << ": b = " << b << std::endl;
        }

        #pragma omp task if(deferred)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * c));
            std::cout << "thread " << omp_get_thread_num() << ": c = " << c << std::endl;
        }
    }

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
