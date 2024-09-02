#include <chrono>
#include <cmath>
#include <iostream>


int main(int argc, char *argv[]) {
    // default parameters
    size_t nx = 4096;  // number of points in x direction
    size_t ny = 4096;  // number of points in y direction
    size_t nIt = 64;   // number of iterations to be performed

    // override with command line arguments
    int i = 1;
    if (argc > i) nx = atoi(argv[i]);
    ++i;
    if (argc > i) ny = atoi(argv[i]);
    ++i;
    if (argc > i) nIt = atoi(argv[i]);
    ++i;
    
    // allocate data
    auto u = new double[nx * ny];
    auto uNew = new double[nx * ny];

    // init fields - 0 on the inside, 1 at the boundaries
    for (size_t j = 0; j < ny; ++j) {
        for (size_t i = 0; i < nx; ++i) {
            if (0 == i || 0 == j || nx - 1 == i || ny - 1 == j) {
                u[j * nx + i] = 0;
                uNew[j * nx + i] = 0;
            } else {
                u[j * nx + i] = 1;
                uNew[j * nx + i] = 1;
            }
        }
    }

    // start measurement
    auto start = std::chrono::steady_clock::now();

    // perform nIt iterations
    for (size_t i = 0; i < nIt; ++i) {
        // update all inner points
        for (size_t j = 1; j < ny - 1; ++j) {
            #pragma omp parallel for
            for (size_t i = 1; i < nx - 1; ++i) {
                uNew[j * nx + i] = 0.25 * (u[j * nx + i - 1] + u[j * nx + i + 1] + u[(j - 1) * nx + i] + u[(j + 1) * nx + i]);
            }
        }

        // swap source and destination array
        std::swap(u, uNew);
    }

    // finish measurement
    auto end = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>(end - start);

    std::cout << "  #cells / #it:  " << nx * ny << " / " << nIt << "\n";
    std::cout << "  elapsed time:  " << 1e3 * elapsedSeconds.count() << " ms\n";
    std::cout << "  per iteration: " << 1e3 * elapsedSeconds.count() / nIt << " ms\n";
    std::cout << "  MLUP/s:        " << 1e-6 * nx * ny * nIt / elapsedSeconds.count() << "\n";

    // check solution - compute the final residual
    double res = 0;
    for (size_t j = 1; j < ny - 1; ++j) {
        for (size_t i = 1; i < nx - 1; ++i) {
            const double localRes = 4 * u[j * nx + i] - (u[j * nx + i - 1] + u[j * nx + i + 1] + u[(j - 1) * nx + i] + u[(j + 1) * nx + i]);
            res += localRes * localRes;
        }
    }

    res = sqrt(res);
    std::cout << "  Final residual is " << res << std::endl;

    // clean up
    delete[] u;
    delete[] uNew;

    return 0;
}
