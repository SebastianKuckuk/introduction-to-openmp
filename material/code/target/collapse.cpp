#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp target teams distribute parallel for simd collapse(2)
    for (auto i = 0; i < 2; ++i)
        for (auto j = 0; j < 5; ++j)
            printf("Team %d, thread %d, i = %d\n", omp_get_team_num(), omp_get_thread_num(), i * 5 + j);
}
