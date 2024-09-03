#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp target
    #pragma omp teams parallel num_teams(2) thread_limit(2)
        printf("Team %d, thread %d\n", omp_get_team_num(), omp_get_thread_num());
}
