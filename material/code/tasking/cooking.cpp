#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << 1e3 * (omp_get_wtime() - start) << ": Cutting raw fries done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << 1e3 * (omp_get_wtime() - start) << ": Cutting tomatoes done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << 1e3 * (omp_get_wtime() - start) << ": Preparing salad done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << 1e3 * (omp_get_wtime() - start) << ": Baking fries done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << 1e3 * (omp_get_wtime() - start) << ": Baking bun done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << 1e3 * (omp_get_wtime() - start) << ": Frying patty done" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << 1e3 * (omp_get_wtime() - start) << ": Assembly done" << std::endl;

    std::cout << "Meal completed after " << 1e3 * (omp_get_wtime() - start) << std::endl;
}
