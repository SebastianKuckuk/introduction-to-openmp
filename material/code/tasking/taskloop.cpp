#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    #pragma omp parallel num_threads(2)
    #pragma omp single
    {
        #pragma omp taskloop
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));
            std::cout << "thread " << omp_get_thread_num() << ": i = " << i << std::endl;
        }
    }

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
