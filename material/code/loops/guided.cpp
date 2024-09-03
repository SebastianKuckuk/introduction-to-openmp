#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    constexpr auto N = 128;

    #pragma omp parallel for num_threads(8) schedule(guided)
    for (auto i = 0; i < N; ++i)
        std::this_thread::sleep_for(std::chrono::milliseconds(i));

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
