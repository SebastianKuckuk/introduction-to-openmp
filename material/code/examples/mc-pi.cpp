#include <chrono>
#include <cmath>
#include <iostream>
#include <random>


int main(int argc, char *argv[]) {
    // default parameters
    size_t nSample = 32 * 1024;  // number of sample points

    // override with command line arguments
    int i = 1;
    if (argc > i) nSample = atoi(argv[i]);
    ++i;
    
    // start measurement
    auto start = std::chrono::steady_clock::now();

    // draw nSamples points and check if they are in the target region
    size_t numHits = 0;

    // initialize a random number generator
    auto seed = 0;
    std::mt19937_64 rng(seed);
    // initialize a uniform distribution in [0 ... 1]
    std::uniform_real_distribution<double> uniform(0., 1.);

    for (size_t i = 0; i < nSample; ++i) {
        auto x = uniform(rng);
        auto y = uniform(rng);

        if (x * x + y * y <= 1.)
            ++numHits;
    }

    // finish measurement
    auto end = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>(end - start);

    std::cout << "  #samples:     " << nSample << "\n";
    std::cout << "  elapsed time: " << 1e3 * elapsedSeconds.count() << " ms\n";
    std::cout << "  MLUP/s:       " << 1e-6 * nSample / elapsedSeconds.count() << "\n";

    // compute and print final solution
    auto pi = 4. * ((double)numHits / nSample);
    std::cout << "  Estimate for pi is " << pi << std::endl;
    std::cout << "  Error is " << std::abs(pi - M_PI) / M_PI << std::endl;

    return 0;
}
