#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
    constexpr auto N = 1024;
    int vec[N];

    for (auto i = 0; i < N; ++i)
        vec[i] = i;

    std::cout << vec[N - 1] << std::endl;
}
