#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    #pragma omp parallel num_threads(4)
    {
        int tid = 1; //# implicit private(tid)
        #pragma omp single copyprivate(tid)
        {
            tid = omp_get_thread_num();
        } //# implicit barrier

        std::cout << tid << std::endl;
    }
}
