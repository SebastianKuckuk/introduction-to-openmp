#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    #pragma omp parallel for
    for (size_t i = 0; i < vec.size(); ++i)
        vec[i] += 10;

    #pragma omp parallel for
    for (auto it = vec.begin(); it != vec.end(); ++it)
        *it += 10;

    #pragma omp parallel for
    for (auto& val : vec)
        val += 10;

    for (const auto& val : vec)
        std::cout << val << " ";
    std::cout << std::endl;
}
