#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    int rawFries, fries, tomatoes, salad, patty, bun;

    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task depend(out : rawFries)
        #pragma omp critical (knife)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << 1e3 * (omp_get_wtime() - start) << ": Cutting raw fries done" << std::endl;
        }

        #pragma omp task depend(out : tomatoes)
        #pragma omp critical (knife)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << 1e3 * (omp_get_wtime() - start) << ": Cutting tomatoes done" << std::endl;
        }

        #pragma omp task depend(out : salad)
        #pragma omp critical (knife)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << 1e3 * (omp_get_wtime() - start) << ": Preparing salad done" << std::endl;
        }

        #pragma omp task depend(in : rawFries) depend(out : fries)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << 1e3 * (omp_get_wtime() - start) << ": Baking fries done" << std::endl;
        }

        #pragma omp task depend(out : bun)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << 1e3 * (omp_get_wtime() - start) << ": Baking bun done" << std::endl;
        }

        #pragma omp task depend(out : patty)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << 1e3 * (omp_get_wtime() - start) << ": Frying patty done" << std::endl;
        }

        #pragma omp task depend(in : fries, bun, patty, tomatoes, salad)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << 1e3 * (omp_get_wtime() - start) << ": Assembly done" << std::endl;
        }
    }

    std::cout << "Meal completed after " << 1e3 * (omp_get_wtime() - start) << std::endl;
}
