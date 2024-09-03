#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    //#pragma omp parallel for
    //for (float i = 0; i < vec.size(); ++i)
    //    vec[i] += 10;

    //#pragma omp parallel for
    //for (size_t i = 1; i < vec.size(); i *= 2)
    //    vec[i] += 10;

    //auto test = [&](size_t i){return i < vec.size();};
    //#pragma omp parallel for
    //for (size_t i = 0; test(i); ++i)
    //    vec[i] += 10;

    //#pragma omp parallel for
    //for (size_t i = 0, j = 1; i < vec.size(); ++i, ++j)
    //    vec[i] += 10;

    for (const auto& val : vec)
        std::cout << val << " ";
    std::cout << std::endl;
}
