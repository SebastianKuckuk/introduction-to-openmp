#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    constexpr auto N = 4, M = 4;

    #pragma omp parallel for num_threads(8) collapse(2)
    for (auto j = 0; j < M; ++j) {
        for (auto i = 0; i < N; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(j * N + i));
            std::cout << "i = " << i << ", j = " << j << ", threadId = " << omp_get_thread_num() << std::endl;
        }
    }

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
