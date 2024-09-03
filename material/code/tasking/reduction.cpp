#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    auto start = omp_get_wtime();

    int a = 1, b = 5, c = 10;
    int sum = 0;

    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp taskgroup task_reduction(+ : sum)
        {
            #pragma omp task in_reduction(+ : sum)
                sum += a;

            #pragma omp task in_reduction(+ : sum)
                sum += b;

            #pragma omp task in_reduction(+ : sum)
            {
                sum += c;
                #pragma omp task in_reduction(+ : sum)
                    sum += c;
            }
        } //# end of taskgroup - sum available

        #pragma omp task
            std::cout << "thread " << omp_get_thread_num() << ": sum = " << sum << std::endl;
    }

    auto end = omp_get_wtime();
    std::cout << "Total time: " << 1e3 * (end - start) << " ms" << std::endl;
}
