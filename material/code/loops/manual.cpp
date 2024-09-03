#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    constexpr auto N = 1024;
    int vec[N];

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();              //# get thread number
        int nt = omp_get_num_threads();              //# get number of threads
        int per_thread = N / nt;                     //# elements per thread (rounded down)
        int remainder = N % nt;                      //# remaining elements (due to rounding)
        int lower  = tid * per_thread;               //# start of this thread's chunk
        lower += tid < remainder ? tid : remainder;  //# modification for uneven chunk size
        int upper  = lower + per_thread;             //# end of this thread's chunk
        upper += tid < remainder ? 1 : 0;            //# modification for uneven chunk size

        for (int i = lower; i < upper; ++i)          //# loop over this thread's chunk
            vec[i] = i;                              //# vector element initialization
    }

    std::cout << vec[N - 1] << std::endl;
}
