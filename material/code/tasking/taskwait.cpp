#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    int a = 1, b = 2, c = 3;

    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * a));
            std::cout << "thread " << omp_get_thread_num() << ": a = " << a << std::endl;
        }

        #pragma omp task
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * b));
            std::cout << "thread " << omp_get_thread_num() << ": b = " << b << std::endl;
        }

        #pragma omp task
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * c));
            std::cout << "thread " << omp_get_thread_num() << ": c = " << c << std::endl;

            #pragma omp task
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10 * c));
                std::cout << "thread " << omp_get_thread_num() << ": recursive task c = " << c << std::endl;
            }
        }

        //# this taskwait will not include the recursive task above
        #pragma omp taskwait

        #pragma omp task
        std::cout << "thread " << omp_get_thread_num() << ": all tasks finished" << std::endl;
    }

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
