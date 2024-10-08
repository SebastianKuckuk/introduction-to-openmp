#include <chrono>
#include <cmath>
#include <iostream>


int main(int argc, char *argv[]) {
    // default parameters
    size_t nx = 64*1024*1024;  // number of points
    size_t nIt = 4;            // number of iterations to be performed

    // override with command line arguments
    int i = 1;
    if (argc > i) nx = atoi(argv[i]);
    ++i;
    if (argc > i) nIt = atoi(argv[i]);
    ++i;
    
    // allocate data
    auto src = new double[nx];
    auto dest = new double[nx];

    #pragma omp target enter data map(alloc : src[0 : nx], dest[0 : nx])

    // init array elements with their index values
    #pragma omp target teams distribute parallel for
    for (size_t i = 0; i < nx; ++i) {
        src[i] = i;
        dest[i] = i;
    }

    // start measurement
    auto start = std::chrono::steady_clock::now();

    // perform nIt iterations
    for (size_t i = 0; i < nIt; ++i) {
        std::cout << "Iteration " << i << std::endl;

        // start iteration measurement
        auto startIt = std::chrono::steady_clock::now();

        // copy array elements and increase each by one
        #pragma omp target teams distribute parallel for
        for (size_t i = 0; i < nx; ++i)
            dest[i] = src[i] + 1;

        // swap source and destination array
        std::swap(src, dest);

        // finish measurement
        auto endIt = std::chrono::steady_clock::now();
        auto elapsedSecondsIt = std::chrono::duration<double>(endIt - startIt);

        std::cout << "  elapsed time:  " << 1e3 * elapsedSecondsIt.count() << " ms\n";
        std::cout << "  bandwidth:     " << 1e-9 * 2 * sizeof(double) * nx / elapsedSecondsIt.count() << " GB/s\n";
        std::cout << std::endl;
    }

    // finish measurement
    auto end = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>(end - start);

    #pragma omp target exit data map(from : src[0 : nx], dest[0 : nx])

    std::cout << "Accumulated" << std::endl;
    std::cout << "  #cells / #it:  " << nx << " / " << nIt << "\n";
    std::cout << "  elapsed time:  " << 1e3 * elapsedSeconds.count() << " ms\n";
    std::cout << "  per iteration: " << 1e3 * elapsedSeconds.count() / nIt << " ms\n";
    std::cout << "  MLUP/s:        " << 1e-6 * nx * nIt / elapsedSeconds.count() << "\n";
    std::cout << "  bandwidth:     " << 1e-9 * 2 * sizeof(double) * nx * nIt / elapsedSeconds.count() << " GB/s\n";

    // check solution - each element should be increased by 
    for (size_t i = 0; i < nx; ++i) {
        if (i + nIt != src[i]) {
            std::cout << "  Stream check failed for element " << i << " (expected " << i + nIt << " but got " << src[i] << ")" << std::endl;
            break;
        }
    }

    std::cout << "  Stream check completed" << std::endl;

    // clean up
    delete[] src;
    delete[] dest;

    return 0;
}
