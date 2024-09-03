#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int a = 10;
    static int b = 20;

    #pragma omp target teams parallel
    if (0 == omp_get_team_num() && 0 == omp_get_thread_num()) {
        printf("a = %d, b = %d\n", a, b);
        a *= 10;
        b *= 10;
    }

    printf("a = %d, b = %d\n", a, b);
}
