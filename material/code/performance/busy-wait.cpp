#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel
    {
        auto start = omp_get_wtime();
        auto duration = 0.;
        while (duration < 1.000) //# seconds
           duration = omp_get_wtime() - start;
    }
}
