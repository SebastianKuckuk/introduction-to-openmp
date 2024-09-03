#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    //# pragma directive
    #pragma omp parallel num_threads(4)
        #pragma omp critical
            std::cout << omp_get_thread_num() << std::endl;

    //# pragma operator
    _Pragma("omp parallel num_threads(4)")
        _Pragma("omp critical")
            std::cout << omp_get_thread_num() << std::endl;

    //# c++ attribute specifier
    [[ omp :: sequence(directive(parallel, num_threads(4)), directive(critical)) ]]
            std::cout << omp_get_thread_num() << std::endl;
}
