#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    #pragma omp parallel num_threads(4)
    #pragma omp single
    {
        for (int t = 0; t < 10; ++t)
        {
            #pragma omp task untied
            {
                auto start = omp_get_wtime();

                #pragma omp critical
                    std::cout << "thread " << omp_get_thread_num() << " started work on task " << t << std::endl;

                for (int i = 0; i < 10; ++i) {
                    #pragma omp critical
                        std::cout << "thread " << omp_get_thread_num() << " works on task " << t << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    #pragma omp taskyield
                }

                auto end = omp_get_wtime();

                #pragma omp critical
                    std::cout << "thread " << omp_get_thread_num() << " finished work on task " << t << " after " << 1e3 * (end - start) << " ms" << std::endl;
            }
        }
    }

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
