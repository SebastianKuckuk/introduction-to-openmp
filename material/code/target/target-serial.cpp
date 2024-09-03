#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp target
    for (auto i = 0; i < 10; ++i)
        printf("%d\n", i);
}
