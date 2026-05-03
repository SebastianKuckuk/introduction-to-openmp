#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    constexpr auto N = 1024;
    int vec[N];

    int last;

    #pragma omp parallel for lastprivate(last)
        for (auto i = 0; i < N; ++i) {
            vec[i] = i;
            last = vec[i];
        }

    std::cout << last << " should be " << vec[N - 1] << std::endl;
}
