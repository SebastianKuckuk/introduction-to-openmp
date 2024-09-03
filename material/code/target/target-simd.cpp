#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp target teams distribute parallel for simd
    for (auto i = 0; i < 10; ++i)
        printf("Team %d, thread %d, i = %d\n", omp_get_team_num(), omp_get_thread_num(), i);
}
