#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    #pragma omp parallel
    #pragma omp single
    {
        int privateVar = 5;
        #pragma omp task // implicit firstprivate(privateVar)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * privateVar));
            std::cout << "thread " << omp_get_thread_num() << ": privateVar = " << privateVar << std::endl;
            privateVar += 10;
        }

        std::cout << "thread " << omp_get_thread_num() << ": privateVar = " << privateVar << std::endl;
    }

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
