#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>

int main(int argc, char *argv[]) {
    int flag = 0;

    #pragma omp parallel num_threads(2)
    {
      if (omp_get_thread_num() == 0) {
        flag = 1;
        #pragma omp flush
      } else {
        while (!flag) {
          #pragma omp flush
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        /* some work */
      }
    }
}
