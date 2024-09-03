#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel num_threads(4)
    {
        auto start = omp_get_wtime();

        std::this_thread::sleep_for(std::chrono::milliseconds(128 + 32 * omp_get_thread_num()));

        auto end = omp_get_wtime();
        std::cout << "Time for thread " << omp_get_thread_num() << " : " << 1e3 * (end - start) << " ms" << std::endl;
    }
}
