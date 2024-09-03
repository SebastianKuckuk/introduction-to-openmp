#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp target
    #pragma omp teams num_teams(2)
    #pragma omp distribute parallel for
    for (auto i = 0; i < 10; ++i)
        printf("Team %d, thread %d, i = %d\n", omp_get_team_num(), omp_get_thread_num(), i);
}
