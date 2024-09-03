#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    //# serial execution
    std::cout << "Hello from thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << std::endl;
}
