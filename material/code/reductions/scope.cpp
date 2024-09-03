#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int sum = 0;
    #pragma omp parallel
    {
        //# sum must not be private here
        #pragma omp scope reduction( + : sum )
        {
            #pragma omp for
            for (auto i = 0; i < 1024; ++i)
                sum += 1;
        } //# implicit barrier - sum is available

        if (12 == omp_get_thread_num() || 24 == omp_get_thread_num())
            std::cout << sum << std::endl;
    }

    std::cout << sum << std::endl;
}
